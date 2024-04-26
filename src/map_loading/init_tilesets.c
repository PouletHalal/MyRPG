/*
** EPITECH PROJECT, 2024
** test
** File description:
** init_tilesets
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maps.h"
#include "tilesets.h"

int add_node(tileset_t *tileset, char *line, int nb_tileset)
{
    char **args = my_str_to_word_array(line, ":");
    tileset_t new = {0};

    if (array_len(args) != 6)
        return -1;
    new.nb_tileset = nb_tileset;
    new.name = strdup(args[0]);
    new.tileset = sfTexture_createFromFile(args[1], NULL);
    new.size = (sfVector2f) {atoi(args[2]), atoi(args[3])};
    new.tile_size = (sfVector2f) {atoi(args[4]), atoi(args[5])};
    free_array(args);
    *tileset = new;
    return 0;
}

tileset_t *init_tilesets(void)
{
    FILE *stream = fopen(tileset_conf, "r");
    char *line = NULL;
    size_t size = 0;
    tileset_t *tileset_list = NULL;
    int nb_tileset = 0;

    if (getline(&line, &size, stream) < 0)
        return NULL;
    nb_tileset = atoi(line);
    tileset_list = malloc(sizeof(tileset_t) * (nb_tileset));
    tileset_list->nb_tileset = nb_tileset;
    for (int i = 0; getline(&line, &size, stream) > 0 && i < nb_tileset; ++i) {
        if (add_node(&(tileset_list[i]), line, nb_tileset) < 0)
            return NULL;
    }
    return tileset_list;
}
