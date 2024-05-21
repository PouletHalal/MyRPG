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

static bool is_out_of_border(sfFloatRect bounds, sfVector2f offset,
    map_list_t *map_list)
{
    if (offset.y < 0 && bounds.top <= 0 + offset.y)
        return true;
    printf("%f %f, %f %f\n", bounds.top, bounds.height, map_list->maps->size.y, offset.y);
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

    if (collision_map == NULL)
        return false;
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
    printf("oui\n");
    if (tile_collision(new_pos, collision_map))
        return true;
    return false;
}
