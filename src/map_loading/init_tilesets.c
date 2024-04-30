/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** init_tilesets
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maps.h"
#include "tilesets.h"
#include "error_handling.h"
#include "temp.h"

int add_node(tileset_t *tileset, char *line, int nb_tileset)
{
    char **args = my_str_to_word_array(line, ":");
    tileset_t new = {0};

    if (len_array(args) != 6) {
        display_and_return(NULL, 2, "Invalid nbr of args -->", line);
        return -1;
    }
    new.nb_tileset = nb_tileset;
    new.name = strdup(args[0]);
    new.tileset = sfTexture_createFromFile(args[1], NULL);
    if (new.tileset == NULL) {
        display_and_return(NULL, 3, "Fail openning: ", args[1], "\n");
        return -1;
    }
    new.size = (sfVector2f) {atoi(args[2]), atoi(args[3])};
    new.tile_size = (sfVector2f) {atoi(args[4]), atoi(args[5])};
    free_array(args);
    *tileset = new;
    return 0;
}

void init_textures(world_t *world)
{

    for (int i = 0; i < ANIM_END; i++)
        world->texture_list[i] = sfTexture_createFromFile(animation_list[i].filename, NULL);
}

tileset_t *init_tilesets(void)
{
    FILE *stream = fopen(tileset_conf, "r");
    char *line = NULL;
    size_t size = 0;
    tileset_t *tileset_list = NULL;
    int nb_tileset = 0;

    if (openning_and_reading(stream, tileset_conf, &line) < 0)
        return NULL;
    nb_tileset = atoi(line);
    tileset_list = malloc(sizeof(tileset_t) * (nb_tileset));
    tileset_list->nb_tileset = nb_tileset;
    for (int i = 0; getline(&line, &size, stream) > 0 && i < nb_tileset; ++i) {
        if (add_node(&(tileset_list[i]), line, nb_tileset) < 0) {
            fclose(stream);
            return NULL;
        }
    }
    fclose(stream);
    return tileset_list;
}
