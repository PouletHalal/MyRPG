/*
** EPITECH PROJECT, 2024
** My_rpg
** File description:
** Sys Render file
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

static void spawn_entity(world_t *world)
{
    int player = find_player(world);
    sfVector2f new_pos = world->entity[player].comp_position.position;
    sfVector2f offset = {-50 + rand() % 100, -50 + rand() % 100};

    if (offset.x < 20 && offset.x > -20)
        offset.x += 50;
    new_pos.x += offset.x;
    new_pos.y += offset.y;
    if (world->key_pressed[sfKeyLControl] && world->key_pressed[sfKeyF])
        init_mob(TXT_FDP, world, new_pos);
}

static void analyse_events(win_t *window, world_t *world)
{
    sfEvent *event = &window->event;

    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window->window);
    if (event->type == sfEvtKeyPressed){
        world->key_pressed[event->key.code] = sfTrue;
        spawn_entity(world);
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
