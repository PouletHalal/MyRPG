/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys stat
*/

#include "temp.h"

void do_attack(entity_t *attack, entity_t *defense)
{
    if ((attack->mask & defense->mask & COMP_STAT) != COMP_STAT)
        return;
    if (defense->comp_stat.clock > 0)
        return;
    if (attack->comp_stat.do_damage == sfFalse)
        return;
    if (attack->comp_stat.faction == defense->comp_stat.faction)
        return;
    defense->comp_stat.health -=
    attack->comp_stat.damage - defense->comp_stat.defense;
    defense->comp_stat.clock = defense->comp_stat.invinsibility_frames;
}

void respawn_entity(entity_t *entity)
{
    comp_stat_t *stat = &entity->comp_stat;

    stat->health = stat->max_health;
    entity->comp_position.position = entity->comp_position.spawn;
    for (int i = 0; i < MAX_EFFECT; i++)
        stat->effect[i] = NULL;
}

static void next_frame(entity_t *entity, world_t *world)
{
    comp_stat_t *stat = &entity->comp_stat;

    loop_effect(entity);
    if (stat->health <= 0.) {
        if (stat->do_respawn) {
            respawn_entity(entity);
            return;
        }
        if ((entity->mask & COMP_RENDER) == COMP_RENDER) {
            entity->mask = COMP_NONE;
            sfSprite_destroy(entity->comp_render.sprite);
        }
        return;
    }
    stat->health += stat->health_regen;
    if (stat->health > stat->max_health)
        stat->health = stat->max_health;
    if (stat->clock > 0)
        stat->clock -= 1;
}

void sys_stat(world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_STAT) == COMP_STAT)
            next_frame(&world->entity[i], world);
}
