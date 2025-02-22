/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys mob
*/

#include <math.h>
#include <stdlib.h>
#include "temp.h"
#include "player.h"
#include "rendering.h"
#include "window.h"
#include "mob.h"

static void update_mob_healthbar(world_t *world, entity_t *mob,
    sfVector2f mob_pos)
{
    sfIntRect rect = world->entity[mob->comp_mob.healthbar_id].comp_render.
    current_animation->base_text_rect;

    rect.width = mob->comp_stat.health / mob->comp_stat.max_health *
    world->entity[mob->comp_mob.healthbar_id].comp_render.current_animation->
    base_text_rect.width;
    world->entity[mob->comp_mob.healthbar_id].comp_render.is_visible = 1;
    sfSprite_setTextureRect(
        world->entity[mob->comp_mob.healthbar_id].comp_render.sprite, rect);
    world->entity[mob->comp_mob.healthbar_id].comp_position.position =
    (sfVector2f){mob_pos.x, mob_pos.y - mob->comp_render.current_animation->
    frame_size.y * mob->comp_render.current_animation->scale.y / 3};
}

static void follow_move(entity_t *mob, entity_t *player, world_t *world)
{
    sfVector2f mob_pos = mob->comp_position.position;
    sfVector2f player_pos = player->comp_position.position;
    double hyp = sqrt(pow((player_pos.x - mob_pos.x), 2) +
    pow((player_pos.y - mob_pos.y), 2));
    double cos = (player_pos.x - mob_pos.x) / hyp;
    double sin = (player_pos.y - mob_pos.y) / hyp;

    add_vector(mob, (sfVector2f)
    {cos * mob->comp_mob.speed, sin * mob->comp_mob.speed}, 1);
    update_mob_healthbar(world, mob, mob_pos);
    update_sprite_direction(mob);
}

static sfBool check_range(entity_t *mob, entity_t *player)
{
    sfVector2f mob_pos = mob->comp_position.position;
    sfVector2f player_pos = player->comp_position.position;

    if ((mob_pos.x - player_pos.x) * (mob_pos.x - player_pos.x) +
    (mob_pos.y - player_pos.y) * (mob_pos.y - player_pos.y) <=
    mob->comp_mob.range * mob->comp_mob.range)
        return sfTrue;
    return sfFalse;
}

static void check_clone_dispawn(entity_t *mob, entity_t *player,
    world_t *world)
{
    sfVector2f mob_pos = mob->comp_position.position;
    sfVector2f player_pos = player->comp_position.position;

    if (mob->comp_mob.is_clone && (mob->comp_position.world != world->map_id
    || (mob_pos.x - player_pos.x) * (mob_pos.x - player_pos.x) +
    (mob_pos.y - player_pos.y) * (mob_pos.y - player_pos.y) > DISPAWN_RANGE))
        kill_entity(mob, world);
    if (mob->comp_mob.healthbar_id != 0)
        world->entity[mob->comp_mob.healthbar_id].comp_render.is_visible = 0;
}

static void next_frame(entity_t *entity, world_t *world, win_t *win)
{
    int player = find_comp(world, COMP_PLAYER);
    int ran = rand();

    if (player == -1)
        return;
    if (entity->comp_position.world != world->map_id)
        return check_clone_dispawn(entity, &world->entity[player], world);
    if (entity->comp_mob.does_follow && entity->comp_mob.is_alive)
        if (check_range(entity, &world->entity[player]))
            return follow_move(entity, &world->entity[player], world);
    if (entity->comp_mob.does_rand_spawn &&
    entity->comp_mob.mob_count < entity->comp_mob.mob_cap
    && (ran % 10000) / 100. < entity->comp_mob.spawn_rate)
        spawn_copy(entity, world, (ran % 360) * M_PI / 180., win);
    check_clone_dispawn(entity, &world->entity[player], world);
}

void sys_mob(world_t *world, win_t *win)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_MOB) == COMP_MOB)
            next_frame(&world->entity[i], world, win);
}
