/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** view
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"
#include "maps.h"

void init_cam(win_t *window, world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask & COMP_PLAYER == COMP_PLAYER)
            sfView_setCenter(window->cam.view,
            world->entity[i].comp_position.position);
    sfRenderWindow_setView(window->window, window->cam.view);
}

void init_view(win_t *window)
{
    window->cam.view_rect = (sfFloatRect) {0., 0., 624, 351};
    window->cam.view = sfView_createFromRect(window->cam.view_rect);
    sfRenderWindow_setView(window->window, window->cam.view);
}
