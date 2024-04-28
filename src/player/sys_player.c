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
#include "maps.h"
#include "player.h"

int find_player(world_t *world)
{
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_PLAYER) == COMP_PLAYER)
            return i;
    return -1;
}

void player_events(win_t *window, entity_t *entity, map_list_t *map_list)
{
    player_movements(window, entity, map_list);
    sfRenderWindow_setView(window->window, window->cam.view);
}

void sys_player(win_t *window, world_t *world, map_list_t *map_list)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_PLAYER) == COMP_PLAYER)
            player_events(window, &(world->entity[i]), map_list);
}
