/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** map_drawing
*/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "maps.h"
#include "tilesets.h"
#include "error_handling.h"

static void draw_tile(map_t *map, char *sep, sfIntRect *rect,
    tileset_t *tileset)
{
    sfSprite *temp = sfSprite_create();
    int nb_tiles_per_line = (tileset->size.x / tileset->tile_size.x);

    sfSprite_setTexture(temp, map->spritesheet, sfTrue);
    rect->left = tileset->tile_size.x * ((atoi(sep)) % nb_tiles_per_line);
    rect->top = tileset->tile_size.y * ((atoi(sep)) / nb_tiles_per_line);
    sfSprite_setTextureRect(temp, *rect);
    sfSprite_setPosition(temp, (sfVector2f)
    {map->sprite.pos.x, map->sprite.pos.y});
    sfRenderTexture_drawSprite(map->map, temp, NULL);
    sfRenderTexture_display(map->map);
    sfSprite_destroy(temp);
}

static void update_pos(map_t *map, sfVector2f tile_size)
{
    map->sprite.pos.x += tile_size.x;
    if (map->sprite.pos.x >= map->size.x) {
        map->sprite.pos.x = 0;
        map->sprite.pos.y += tile_size.y;
    }
}

void read_line(map_t *map, char *line, tileset_t *tileset, int line_id)
{
    char *sep = NULL;
    sfIntRect rect = {0, 0, tileset->tile_size.x, tileset->tile_size.y};
    int tile_id = 0;

    sep = strtok(line, ",");
    while (sep != NULL) {
        map->csv_map[line_id][tile_id] = atoi(sep);
        if (atoi(sep) != -1) {
            draw_tile(map, sep, &rect, tileset);
        }
        update_pos(map, tileset->tile_size);
        sep = strtok(NULL, ",");
        tile_id += 1;
    }
}

void parse_map(map_t *map, char const *name, tileset_t *tileset)
{
    FILE *stream = fopen(name, "r");
    char *line = NULL;
    size_t size = 0;
    int nb_lines = 0;

    if (test_open(stream, name) == -1 || tileset == NULL)
        return;
    map->csv_map = malloc(sizeof(int *) *
    (map->size.y / tileset->tile_size.x) + 1);
    while (getline(&line, &size, stream) > 0) {
        map->csv_map[nb_lines] = malloc(sizeof(int) *
        map->size.x / tileset->tile_size.x);
        read_line(map, line, tileset, nb_lines);
        nb_lines += 1;
    }
    map->csv_map[nb_lines - 1] = NULL;
    free(line);
    fclose(stream);
}
