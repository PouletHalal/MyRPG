/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys Render file
*/

#include <SFML/Graphics.h>
#include <SFML/Window/Keyboard.h>
#include <stdlib.h>
#include "temp.h"
#include "maps.h"
#include "player.h"

int find_player(world_t *world)
{
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_PLAYER) == COMP_PLAYER)
            return i;
    return -1;
}

static void update_player_animation(entity_t *entity)
{
    sfVector2f *velocity = &(entity->comp_position.velocity);

    if (is_in_animation(entity))
        return;
    if (is_key_pressed(entity, sfKeySpace)){
        play_animation(entity, ANIM_PROTA_JUMP, false);
        return;
    }
    if (is_key_pressed(entity, sfKeyE)){
        play_animation(entity, ANIM_PROTA_ATTACK, false);
        return;
    }
    if (is_key_pressed(entity, sfKeyA)){
        play_animation(entity, ANIM_PROTA_DODO, false);
        return;
    }
    if (velocity->x == 0 && velocity->y == 0)
        play_animation(entity, ANIM_PROTA_IDLE, true);
    else
        play_animation(entity, ANIM_PROTA_RUN, true);
}

static void next_frame(win_t *window, entity_t *entity, map_list_t *map_list)
{
    sfVector2f *velocity = &(entity->comp_position.velocity);

    velocity->x = 0;
    velocity->y = 0;
    if (is_key_pressed(entity, sfKeyD) && !is_key_pressed(entity, sfKeyQ)
        && !is_colliding(entity, map_list, (sfVector2f){1.5, 0})) {
        update_cam(window, entity, map_list, (sfVector2f){1.5, 0});
        velocity->x += 1.5;
    }
    if (is_key_pressed(entity, sfKeyS) && !is_key_pressed(entity, sfKeyZ) &&
        !is_colliding(entity, map_list, (sfVector2f){0, 1.5})){
        update_cam(window, entity, map_list, (sfVector2f){0, 1.5});
        velocity->y += 1.5;
    }
    if (is_key_pressed(entity, sfKeyQ) && !is_key_pressed(entity, sfKeyD) &&
        !is_colliding(entity, map_list, (sfVector2f){-1.5, 0})){
        update_cam(window, entity, map_list, (sfVector2f){-1.5, 0});
        velocity->x -= 1.5;
    }
    if (is_key_pressed(entity, sfKeyZ) && !is_key_pressed(entity, sfKeyS) &&
        !is_colliding(entity, map_list, (sfVector2f){0, -1.5})){
        update_cam(window, entity, map_list, (sfVector2f){0, -1.5});
        velocity->y -= 1.5;
    }
    update_player_animation(entity);
    update_sprite_direction(entity);
}

void player_events(win_t *window, entity_t *entity, map_list_t *map_list)
{
    next_frame(window, entity, map_list);
    sfRenderWindow_setView(window->window, window->cam.view);
}

void sys_player(win_t *window, world_t *world, map_list_t *map_list)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_PLAYER) == COMP_PLAYER)
            player_events(window, &(world->entity[i]), map_list);
}
    