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

static void mouse_inputs(win_t *window, world_t *world, entity_t *player)
{
    sfEvent *event = &window->event;

    if (event->type == sfEvtMouseButtonPressed) {
        if (event->mouseButton.button == sfMouseLeft) {
            player->comp_input.mouse_left_down = true;
            world->mouse_left_pressed = true;
        }
        if (event->mouseButton.button == sfMouseRight) {
            player->comp_input.mouse_right_down = true;
            world->mouse_right_pressed = true;
        }
    }
    if (event->type == sfEvtMouseButtonReleased) {
        player->comp_input.mouse_left_down = false;
        player->comp_input.mouse_right_down = false;
        world->mouse_left_pressed = false;
        world->mouse_right_pressed = false;
    }
}

static void analyse_events(win_t *window, world_t *world)
{
    sfEvent *event = &window->event;
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window->window);
    mouse_inputs(window, world, player);
    if (event->type == sfEvtKeyPressed && event->key.code != -1){
        world->key_down[event->key.code] = sfTrue;
        world->key_pressed[event->key.code] = sfTrue;
        if (world->key_pressed[sfKeyTab])
            player->comp_inventory.is_open = !player->comp_inventory.is_open;
        if (world->key_pressed[sfKeyK])
            create_item(world, (sfVector2f) {player->comp_position.position.x,
            player->comp_position.position.y + 50}, rand() % world->item_list.nb_items);
    }
    if (event->type == sfEvtKeyReleased){
        world->key_down[event->key.code] = sfFalse;
    }
    if (world->key_down[sfKeyEscape])
        sfRenderWindow_close(window->window);
}

static void exec_input(world_t *world, entity_t *entity, win_t *window)
{
    for (int i = 0; i < NB_KEYS; ++i) {
        if (world->key_down[i] && entity->comp_input.down_func[i] != NULL)
            entity->comp_input.down_func[i](window, world, entity);
        if (world->key_pressed[i] &&
        entity->comp_input.pressed_func[i] != NULL)
            entity->comp_input.pressed_func[i](window, world, entity);
    }
}

void sys_input_and_event(world_t *world, win_t *window)
{
    for (int i = 0; i < NB_KEYS; i++)
        world->key_pressed[i] = sfFalse;
    while (sfRenderWindow_pollEvent(window->window, &(window->event)))
        analyse_events(window, world);
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_INPUT) == COMP_INPUT)
            exec_input(world, &world->entity[i], window);
}
