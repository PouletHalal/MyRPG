/*
** EPITECH PROJECT, 2024
** My_rpg
** File description:
** Sys Render file
*/

#include <SFML/Graphics.h>
#include <SFML/Window/Keyboard.h>
#include <stdlib.h>
#include "temp.h"

static void update_player_animation(entity_t *entity)
{
    sfVector2f *velocity = &(entity->comp_position.velocity);

    if (is_in_animation(entity)){
        return;
    }
    if (is_key_pressed(entity, sfKeySpace)){
        play_animation(entity, ANIM_PROTA_JUMP, false);
        return;
    }
    if (is_key_pressed(entity, sfKeyE)){
        play_animation(entity, ANIM_PROTA_ATTACK, false);
        return;
    }
    if (velocity->x == 0 && velocity->y == 0)
        play_animation(entity, ANIM_PROTA_IDLE, true);
    else
        play_animation(entity, ANIM_PROTA_RUN, true);
}

static void next_frame(entity_t *entity)
{
    sfVector2f *velocity = &(entity->comp_position.velocity);

    velocity->x = 0;
    velocity->y = 0;
    if (is_key_pressed(entity, sfKeyD))
        velocity->x += 5;
    if (is_key_pressed(entity, sfKeyQ))
        velocity->x -= 5;
    if (is_key_pressed(entity, sfKeyS))
        velocity->y += 5;
    if (is_key_pressed(entity, sfKeyZ))
        velocity->y -= 5;
    update_player_animation(entity);
    update_sprite_direction(entity);
}

void sys_player(world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask & COMP_PLAYER == COMP_PLAYER)
            next_frame(&world->entity[i]);
}
