/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** map_rendering
*/

#include "temp.h"
#include "maps.h"

static void is_prio(win_t *window, map_t *map, int priority)
{
    if (map->priority == priority)
        sfRenderWindow_drawSprite(window->window, map->sprite.sprite, NULL);
}

void display_map(win_t *window, map_list_t *map_list, int priority)
{
    if (map_list == NULL)
        return;
    if (sfMusic_getStatus(map_list->music) != sfPlaying)
        sfMusic_play(map_list->music);
    for (int j = 0; j < map_list->nb_layer; ++j) {
        is_prio(window, &(map_list->maps[j]), priority);
    }
}
