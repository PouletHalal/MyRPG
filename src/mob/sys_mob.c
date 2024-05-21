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

static void follow_move(entity_t *mob, entity_t *player)
{
    sfVector2f mob_pos = mob->comp_position.position;
    sfVector2f player_pos = player->comp_position.position;
    double hyp = sqrt(pow((player_pos.x - mob_pos.x), 2) +
    pow((player_pos.y - mob_pos.y), 2));
    double cos = (player_pos.x - mob_pos.x) / hyp;
    double sin = (player_pos.y - mob_pos.y) / hyp;

    add_vector(mob, (sfVector2f)
    {cos * mob->comp_mob.speed, sin * mob->comp_mob.speed}, 1);
}

static sfBool check_range(entity_t *mob, entity_t *player)
{
    sfVector2f mob_pos = mob->comp_position.position;
    sfVector2f player_pos = player->comp_position.position;

    if (sqrt(pow((player_pos.x - mob_pos.x), 2) +
    pow((player_pos.y - mob_pos.y), 2)) <= mob->comp_mob.range)
        return sfTrue;
    return sfFalse;
}

static void next_frame(entity_t *entity, world_t *world, win_t *win)
{
    int player = find_comp(world, COMP_PLAYER);
    int ran = rand();

    play_animation(world, entity, entity->comp_mob.anim_id, true);
    if (player != -1 && entity->comp_mob.does_follow
        && entity->comp_mob.is_alive
        && (entity->mask & COMP_POSITION) == COMP_POSITION &&
        (entity->comp_position.world == world->map_id))
        if (check_range(entity, &world->entity[player]))
            follow_move(entity, &world->entity[player]);
    update_sprite_direction(entity);
    if (entity->comp_mob.does_rand_spawn && player != -1
    && ran % 100 > entity->comp_mob.spawn_rate)
        spawn_copy(entity, world, (ran % 180) * M_PI / 180., win);
}

void sys_mob(world_t *world, win_t *win)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_MOB) == COMP_MOB
        && world->entity[i].comp_position.world == world->map_id)
            next_frame(&world->entity[i], world, win);
}
