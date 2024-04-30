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

bool tile_collision(sfVector2f pos, int **collision_map)
{
    int x = ((pos.x) / TILE_WIDTH);
    int y = ((pos.y) / TILE_HEIGHT);

    if (collision_map[y][x] != -1)
        return true;
    return false;
}

bool is_colliding(entity_t *entity, map_list_t *map_list, sfVector2f offset)
{
    int **collision_map = get_collision_map(map_list);
    sfFloatRect bounds = sfSprite_getGlobalBounds(entity->comp_render.sprite);
    sfVector2f new_pos = {entity->comp_position.position.x + offset.x,
        entity->comp_position.position.y + offset.y};

    if (is_out_of_border(bounds, offset, map_list))
        return true;
    if (collision_map == NULL)
        return false;
    if (tile_collision(new_pos, collision_map)) {
        return true;
    }
    return false;
}
