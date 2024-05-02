/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** parsing
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
    rect->left = TILE_WIDTH * ((atoi(sep)) % nb_tiles_per_line);
    rect->top = TILE_HEIGHT * ((atoi(sep)) / nb_tiles_per_line);
    sfSprite_setTextureRect(temp, *rect);
    sfSprite_setPosition(temp, (sfVector2f)
    {map->sprite.pos.x, map->sprite.pos.y});
    sfRenderTexture_drawSprite(map->map, temp, NULL);
    sfRenderTexture_display(map->map);
    sfSprite_destroy(temp);
}

static void update_pos(map_t *map)
{
    map->sprite.pos.x += TILE_WIDTH;
    if (map->sprite.pos.x >= map->size.x) {
        map->sprite.pos.x = 0;
        map->sprite.pos.y += TILE_HEIGHT;
    }
}

void read_line(map_t *map, char *line, tileset_t *tileset, int line_id)
{
    char *sep = NULL;
    sfIntRect rect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    int tile_id = 0;

    sep = strtok(line, ",");
    while (sep != NULL) {
        map->csv_map[line_id][tile_id] = atoi(sep);
        if (atoi(sep) != -1) {
            draw_tile(map, sep, &rect, tileset);
        }
        update_pos(map);
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
    map->csv_map = malloc(sizeof(int *) * (map->size.y / TILE_WIDTH) + 1);
    while (getline(&line, &size, stream) > 0) {
        map->csv_map[nb_lines] = malloc(sizeof(int) *
        map->size.x / TILE_WIDTH);
        read_line(map, line, tileset, nb_lines);
        nb_lines += 1;
    }
    map->csv_map[nb_lines - 1] = NULL;
    free(line);
    fclose(stream);
}

static sfTexture *get_texture(tileset_t *tileset_list, char *name)
{
    for (int i = 0; i < tileset_list->nb_tileset; ++i) {
        if (strcmp(tileset_list[i].name, name) == 0)
            return tileset_list[i].tileset;
    }
    return display_and_return(NULL, 2, "Unable to find texture -->", name);
}

static tileset_t *get_tileset(tileset_t *tileset_list, char *name)
{
    for (int i = 0; i < tileset_list->nb_tileset; ++i) {
        if (strcmp(tileset_list[i].name, name) == 0) {
            return &(tileset_list[i]);
        }
    }
    return display_and_return(NULL, 2, "Unable to find tileset ->", name);
}

static map_t add_map(char **args, tileset_t *tileset_list)
{
    map_t map = {0};

    map.name = strdup(args[1]);
    map.size = (sfVector2f) {atoi(args[2]), atoi(args[3])};
    map.map = sfRenderTexture_create(map.size.x, map.size.y, sfFalse);
    sfRenderTexture_clear(map.map, sfTransparent);
    map.sprite.sprite = sfSprite_create();
    map.sprite.texture = sfRenderTexture_getTexture(map.map);
    map.sprite.scale = (sfVector2f) {1, 1};
    map.sprite.pos = (sfVector2f) {0, 0};
    map.priority = atoi(args[5]);
    sfSprite_setTexture(map.sprite.sprite, map.sprite.texture, sfFalse);
    map.spritesheet = get_texture(tileset_list, args[4]);
    parse_map(&map, args[0], (get_tileset(tileset_list, args[4])));
    return map;
}

static map_list_t *get_map(char *line, FILE *stream, tileset_t *tileset_list)
{
    char **split = my_str_to_word_array(line, ":\n");
    map_list_t *map = malloc(sizeof(map_list_t));
    size_t size = 0;

    if (len_array(split) != 2)
        return display_and_return(NULL, 2, "Invalid nbr of args ->", line);
    map->name = split[0];
    map->nb_layer = atoi(split[1]);
    if (map->nb_layer <= 0)
        return display_and_return(NULL, 2, "Invalid nbr of layers ->", line);
    map->maps = malloc(sizeof(map_t) * map->nb_layer);
    for (int i = 0; i < map->nb_layer; ++i) {
        if (getline(&line, &size, stream) < 0)
            return display_and_return(NULL, 1, "Fail reading line\n");
        split = my_str_to_word_array(line, ":\n");
        if (len_array(split) != MAP_CONF_NB_ARGS)
            return display_and_return(NULL, 2, "Invalid nbr of args ->", line);
        map->maps[i] = add_map(split, tileset_list);
    }
    return map;
}

map_list_t **init_map(char const *map_file, tileset_t *tileset_list)
{
    FILE *stream = fopen(map_file, "r");
    char *line = NULL;
    size_t size = 0;
    map_list_t **map = NULL;
    int nb_maps = 0;

    if (openning_and_reading(stream, map_file, &line) || !tileset_list)
        return NULL;
    nb_maps = atoi(line);
    if (nb_maps <= 0)
        return display_and_return(NULL, 2, "Invalid nbr of maps ->", line);
    map = calloc(nb_maps + 1, sizeof(map_list_t *));
    for (int i = 0; i < nb_maps; ++i) {
        if (getline(&line, &size, stream) < 0)
            return display_and_return(NULL, 1, "Fail reading line\n");
        map[i] = get_map(line, stream, tileset_list);
        if (map[i] == NULL)
            return NULL;
    }
    return map;
}
