/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys render
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <math.h>
#include "temp.h"
#include "rendering.h"
#include "player.h"
#include "memory.h"

void follow_enemy(entity_t *spell, entity_t *enemy)
{
    sfVector2f spell_pos = {0};
    sfVector2f enemy_pos = {0};
    double hyp = 0.0;
    double cos = 0.0;
    double sin = 0.0;

    if (enemy == NULL)
        return;
    spell_pos = spell->comp_position.position;
    enemy_pos = enemy->comp_position.position;
    hyp = sqrt(pow((enemy_pos.x - spell_pos.x), 2) +
        pow((enemy_pos.y - spell_pos.y), 2));
    cos = (enemy_pos.x - spell_pos.x) / hyp;
    sin = (enemy_pos.y - spell_pos.y) / hyp;
    add_vector(spell, (sfVector2f){cos * spell->comp_spell.speed,
        sin * spell->comp_spell.speed}, 1);
}

static int get_dist(entity_t *entity1, entity_t *entity2)
{
    sfVector2f entity1_pos = entity1->comp_position.position;
    sfVector2f entity2_pos = entity2->comp_position.position;

    return sqrt(pow((entity1_pos.x - entity2_pos.x), 2) +
        pow((entity1_pos.y - entity2_pos.y), 2));
}

static sfBool is_targetable(entity_t *entity, int map_id, entity_t *spell)
{
    if ((entity->mask & COMP_MOB) != COMP_MOB ||
        entity->comp_position.world != map_id ||
        entity->comp_stat.faction == spell->comp_stat.faction ||
        entity->comp_mob.is_alive == sfFalse)
        return sfFalse;
    return sfTrue;
}

entity_t *get_closest(entity_t *entity, world_t *world)
{
    entity_t *closest_entity = NULL;
    int closest_dist = 999999;
    int dist = 0;

    for (int i = 0; i < ENTITY_COUNT; ++i){
        if (!is_targetable(&world->entity[i], world->map_id, entity)
            || is_in_memory(&entity->comp_spell.memory, &world->entity[i]))
            continue;
        dist = get_dist(entity, &world->entity[i]);
        if (dist < closest_dist){
            closest_dist = dist;
            closest_entity = &world->entity[i];
        }
    }
    if (closest_entity == NULL || closest_dist > 300.)
        return NULL;
    return closest_entity;
}

static void follow_closest(entity_t *entity, world_t *world)
{
    entity_t *closest_entity = get_closest(entity, world);
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    if (closest_entity == NULL) {
        add_vector(entity, get_mouv_vector(player), 2);
        return;
    }
    follow_enemy(entity, closest_entity);
}

static void destroy_spell(entity_t *entity, world_t *world)
{
    free_memory(entity->comp_spell.memory);
    if ((entity->mask & COMP_RENDER) == COMP_RENDER) {
        sfTexture_destroy(entity->comp_render.texture);
        sfSprite_destroy(entity->comp_render.sprite);
    }
    entity->mask = COMP_NONE;
}

static sfBool is_piercing(entity_t *entity)
{
    if (entity->comp_spell.target == ONE_ALLY
        || entity->comp_spell.target == ONE_ENNEMY
        || entity->comp_spell.target == SELF)
        return sfFalse;
    return sfTrue;
}

static void next_frame(entity_t *entity, world_t *world)
{
    comp_spell_t *c_spell = &entity->comp_spell;

    if (entity->comp_spell.move_type == FOLLOW)
        follow_closest(entity, world);
    for (int i = 0; i < ENTITY_COUNT; ++i){
        if ((world->entity[i].mask & COMP_MOB) != COMP_MOB
            || !is_close(&world->entity[i], entity, (sfVector2f){20, 20})
            || is_in_memory(&entity->comp_spell.memory, &world->entity[i]))
            continue;
        world->entity[i].comp_stat.health -= c_spell->damage;
        if (entity->comp_spell.effect_index != NO_EFFECT)
            add_effect(world, &world->entity[i], c_spell->effect_index);
        add_to_memory(&entity->comp_spell.memory, &world->entity[i]);
        if (!is_piercing(entity))
            return destroy_spell(entity, world);
    }
    c_spell->duration -= 1;
    if (c_spell->duration <= 0)
        return destroy_spell(entity, world);
    update_sprite_direction(entity);
}

void sys_spell(world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_SPELL) == COMP_SPELL)
            next_frame(&world->entity[i], world);
}
