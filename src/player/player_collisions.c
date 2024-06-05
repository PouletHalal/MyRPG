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

int **get_layer(map_list_t *map_list, char const *name)
{
    for (int i = 0; i < map_list->nb_layer; ++i) {
        if (strcmp(map_list->maps[i].name, name) == 0) {
            return map_list->maps[i].csv_map;
        }
    }
    return NULL;
}

static int get_layer_id(map_list_t *map_list, char const *name)
{
    for (int i = 0; i < map_list->nb_layer; ++i) {
        if (strcmp(map_list->maps[i].name, name) == 0) {
            return i;
        }
    }
    return 0;
}

static bool is_out_of_border(sfFloatRect bounds, sfVector2f offset,
    map_list_t *map_list)
{
    if (offset.y < 0 && bounds.top <= 0)
        return true;
    if (offset.y > 0 &&
        bounds.top + bounds.height >= map_list->maps->size.y)
        return true;
    if (offset.x < 0 && bounds.left <= 0)
        return true;
    if (offset.x > 0 &&
        bounds.left + bounds.width >= map_list->maps->size.x)
        return true;
    return false;
}

bool tile_collision(sfVector2f pos, int **collision_map, sfVector2f tile_size,
    sfVector2f map_size)
{
    int x = ((pos.x) / tile_size.x);
    int y = ((pos.y) / tile_size.y);

    if (collision_map == NULL)
        return false;
    if (x < 0 || y < 0 || y >= map_size.y / tile_size.y ||
        x >= map_size.x / tile_size.x)
        return true;
    printf("x = %d y = %d\n", x, y);
    if (collision_map[y][x] != -1)
        return true;
    return false;
}

static bool is_outside_map(sfVector2f pos, map_list_t *map_list)
{
    if (pos.x < 0 || pos.y < 0)
        return true;
    if (pos.x > map_list->maps->size.x || pos.y > map_list->maps->size.y)
        return true;
    return false;
}

bool is_colliding(world_t *world, entity_t *entity, sfVector2f offset)
{
    map_list_t *map_list = world->map_list[world->map_id];
    int **collision_map = get_layer(map_list, "collision");
    sfFloatRect bounds = entity->comp_hitbox.hitbox;
    sfVector2f new_pos = {entity->comp_position.position.x + offset.x,
        entity->comp_position.position.y + offset.y};

    bounds.left += entity->comp_position.position.x;
    bounds.top += entity->comp_position.position.y;
    if (entity->comp_position.world != world->map_id)
        return true;
    if (entity == NULL)
        return false;
    if (is_out_of_border(bounds, offset, map_list))
        return true;
    if (tile_collision(new_pos, collision_map, map_list->maps[
        get_layer_id(map_list, "collision")].tile_size, map_list->maps->size))
        return true;
    return false;
}
