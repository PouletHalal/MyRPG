/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys render
*/

#include <stdlib.h>
#include <SFML/Window.h>
#include "temp.h"
#include "camera.h"
#include "player.h"

sfBool is_key_pressed(entity_t *entity, sfKeyCode code)
{
    return entity->comp_input.key_pressed[code];
}

sfBool is_key_down(entity_t *entity, sfKeyCode code)
{
    return entity->comp_input.key_down[code];
}

static void spawn_entity(world_t *world)
{
    int player = find_comp(world, COMP_PLAYER);
    sfVector2f new_pos = world->entity[player].comp_position.position;
    sfVector2f offset = {-50 + rand() % 100, -50 + rand() % 100};

    if (offset.x < 20 && offset.x > -20)
        offset.x += 50;
    new_pos.x += offset.x;
    new_pos.y += offset.y;
    if (world->key_pressed[sfKeyLControl] && world->key_pressed[sfKeyF])
        init_mob(world, ANIM_MOB_RUN, new_pos);
}

static void analyse_events(win_t *window, world_t *world)
{
    sfEvent *event = &window->event;
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window->window);
    if (event->type == sfEvtKeyPressed){
        world->key_down[event->key.code] = sfTrue;
        world->key_pressed[event->key.code] = sfTrue;
        npc_collision(window, world, player);
    }
    if (event->type == sfEvtKeyReleased){
        world->key_down[event->key.code] = sfFalse;
    }
    if (world->key_down[sfKeyEscape])
        sfRenderWindow_close(window->window);
}

void sys_input_and_event(world_t *world, win_t *window)
{
    for (int i = 0; i < NB_KEYS; i++)
        world->key_pressed[i] = sfFalse;
    while (sfRenderWindow_pollEvent(window->window, &(window->event)))
        analyse_events(window, world);
}
