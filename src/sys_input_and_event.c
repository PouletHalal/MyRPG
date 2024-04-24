/*
** EPITECH PROJECT, 2024
** My_rpg
** File description:
** Sys Render file
*/

#include <stdlib.h>
#include <SFML/Window.h>
#include "temp.h"

sfBool is_key_pressed(entity_t *entity, sfKeyCode code)
{
    return entity->comp_input.key_pressed[code];
}

static void analyse_events(win_t *window, world_t *world)
{
    sfEvent *event = &window->event;

    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window->window);
    if (event->type == sfEvtKeyPressed){
        world->key_pressed[event->key.code] = sfTrue;
    }
    if (event->type == sfEvtKeyReleased){
        world->key_pressed[event->key.code] = sfFalse;
    }
}

void sys_input_and_event(world_t *world, win_t *window)
{
    while (sfRenderWindow_pollEvent(window->window, &(window->event)))
        analyse_events(window, world);
}
