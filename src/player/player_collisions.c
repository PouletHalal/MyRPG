/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** player_collisions
*/

#include <SFML/Graphics.h>
#include <SFML/Window/Keyboard.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "temp.h"
#include "maps.h"

static int **get_collision_map(map_list_t *map_list)
{
    char **result = NULL;

    for (int i = 0; i < map_list->nb_layer; ++i) {
        if (strcmp(map_list->maps[i].name, "collision") == 0) {
            return map_list->maps[i].csv_map;
        }
    }
    return NULL;
}

static bool is_out_of_border(sfFloatRect bounds, sfVector2f offset,
    map_list_t *map_list)
{
    if (offset.y < 0 && bounds.top <= 0 + offset.y)
        return true;
    if (offset.y > 0 &&
        bounds.top + bounds.height >= map_list->maps->size.y - offset.y)
        return true;
    if (offset.x < 0 && bounds.left <= 0 + offset.x)
        return true;
    if (offset.x > 0 &&
        bounds.left + bounds.width >= map_list->maps->size.x - offset.x)
        return true;
    return false;
}

static bool tile_collision(sfFloatRect bounds, int **collision_map,
    sfVector2f offset)
{
    int y_top = round((bounds.top + bounds.height / 2) / TILE_HEIGHT);
    int y_bot = round((bounds.top - bounds.height / 2) / TILE_HEIGHT);
    int x_left = round((bounds.left + bounds.width / 2) / TILE_WIDTH);
    int x_right = round((bounds.left - bounds.width / 2) / TILE_WIDTH);

    if (offset.y < 0 && (collision_map[y_top + ((int) offset.y)][x_left] != -1
        || collision_map[y_top + ((int) offset.y)][x_right] != -1))
        return true;
    if (offset.y > 0 && (collision_map[y_bot + ((int) offset.y)][x_right] != -1
        || collision_map[y_bot + ((int) offset.y)][x_left] != -1))
        return true;
    if (offset.x < 0 && (collision_map[y_bot][x_left + ((int) offset.x)] != -1
        || collision_map[y_top][x_left + ((int) offset.x)] != -1))
        return true;
    if (offset.x > 0 && (collision_map[y_top][x_right + ((int) offset.x)] != -1
        || collision_map[y_bot][x_right + ((int) offset.x)] != -1))
        return true;
    return false;
}

bool is_colliding(entity_t *entity, map_list_t *map_list, sfVector2f offset)
{
    int **collision_map = get_collision_map(map_list);
    sfFloatRect bounds = sfSprite_getGlobalBounds(entity->comp_render.sprite);

    if (is_out_of_border(bounds, offset, map_list))
        return true;
    if (collision_map == NULL)
        return false;
    if (tile_collision(bounds, collision_map, offset)) {
        return true;
    }
    return false;
}
