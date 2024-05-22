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
#include "rendering.h"
#include "player.h"
#include "hud.h"

int find_comp(world_t *world, int comp)
{
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & comp) == comp)
            return i;
    return -1;
}

static void update_player_animation(world_t *world, entity_t *entity)
{
    sfVector2f velocity = get_mouv_vector(entity);

    if (entity->comp_position.can_move == false)
        return;
    if (is_in_animation(entity))
        return;
    if (is_key_down(entity, sfKeyE))
        return play_animation(world, entity, get_anim_id(world, "prota_attack")
        , false);
    if (is_key_down(entity, sfKeyA))
        return play_animation(world, entity, get_anim_id(world, "prota_dodo"),
        false);
    if (velocity.x == 0 && velocity.y == 0)
        return play_animation(world, entity, get_anim_id(world, "prota_idle"),
        true);
    else {
        return play_animation(world, entity, get_anim_id(world, "prota_run"),
        true);
    }
}

static void next_frame(win_t *window, world_t *world, entity_t *entity)
{
    if (is_key_down(entity, sfKeyD))
        add_vector(entity, (sfVector2f) {1.5, 0.}, 1);
    if (is_key_down(entity, sfKeyS))
        add_vector(entity, (sfVector2f) {0., 1.5}, 1);
    if (is_key_down(entity, sfKeyQ))
        add_vector(entity, (sfVector2f) {-1.5, 0.}, 1);
    if (is_key_down(entity, sfKeyZ))
        add_vector(entity, (sfVector2f) {0., -1.5}, 1);
    update_player_animation(world, entity);
    update_sprite_direction(entity);
}

static void player_events(win_t *window, entity_t *entity, world_t *world)
{
    next_frame(window, world, entity);
    sfRenderWindow_setView(window->window, window->cam.view);
}

void sys_player(win_t *window, world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_PLAYER) == COMP_PLAYER)
            player_events(window, &(world->entity[i]), world);
}
