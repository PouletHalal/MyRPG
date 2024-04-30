/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys mob
*/

#include <math.h>
#include "temp.h"
#include "player.h"

static void follow_move(entity_t *mob, entity_t *player)
{
    sfVector2f mob_pos = mob->comp_position.position;
    sfVector2f player_pos = player->comp_position.position;
    double hyp = sqrt(pow((player_pos.x - mob_pos.x), 2) +
    pow((player_pos.y - mob_pos.y), 2));
    double cos = (player_pos.x - mob_pos.x) / hyp;
    double sin = (player_pos.y - mob_pos.y) / hyp;

    mob->comp_position.velocity.x = cos * mob->comp_mob.speed;
    mob->comp_position.velocity.y = sin * mob->comp_mob.speed;
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

static void next_frame(entity_t *entity, world_t *world)
{
    int player = find_player(world);

    play_animation(entity, ANIM_MOB_RUN, true);
    if (player != -1 && entity->comp_mob.does_follow == sfTrue &&
        (entity->mask & COMP_POSITION) == COMP_POSITION &&
        (world->entity[player].mask & COMP_POSITION) == COMP_POSITION)
        if (check_range(entity, &world->entity[player]))
            follow_move(entity, &world->entity[player]);
        else
            entity->comp_position.velocity = (sfVector2f) {0., 0.};
    update_sprite_direction(entity);
}

void sys_mob(world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_MOB) == COMP_MOB)
            next_frame(&world->entity[i], world);
}

