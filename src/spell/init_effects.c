/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_effects
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "temp.h"
#include "rendering.h"
#include "player.h"
#include "error_handling.h"
#include "effect_parsing.h"

static int get_effect_arg(world_t *world, effect_t *effect, char *line,
    char **split)
{
    for (int i = 0; EFFECT_FLAG[i].name != NULL; i++) {
        if (strcmp(split[0], EFFECT_FLAG[i].name) == 0 &&
            EFFECT_FLAG[i].ptr != NULL) {
                free_array(split);
            return EFFECT_FLAG[i].ptr(world, effect, line);
        }
    }
    free_array(split);
    return 0;
}

static int init_effect(world_t *world, char *filename, int effect_id)
{
    FILE *stream = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    char **split = NULL;

    if (test_open(stream, filename) == -1)
        return 84;
    while (getline(&line, &len, stream) > 0) {
        if (is_eof(line) == 1)
            break;
        split = my_str_to_word_array(line, "= \n\t");
        if (split == NULL)
            return int_display_and_return(84, 3, "Invalid line: ", line, "\n");
        if (get_effect_arg(world, &world->effect_list[effect_id], line, split))
            return 84;
    }
    return fclose(stream);
}

int read_effect_conf(world_t *world)
{
    FILE *stream = fopen(EFFECT_CONF, "r");
    char *line = NULL;
    size_t len = 0;
    int effect_id = 0;

    if (test_open(stream, EFFECT_CONF) == -1)
        return int_display_and_return(84, 1, "Invalid file\n");
    world->effect_list = NULL;
    for (effect_id = 0; getline(&line, &len, stream) > 0; ++effect_id) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (line[0] == '\0')
            break;
        world->effect_list = realloc(world->effect_list,
            sizeof(effect_t) * (effect_id + 1));
        if (init_effect(world, line, effect_id) == 84)
            return 84;
    }
    world->effect_list = realloc(world->effect_list,
        sizeof(effect_t) * (effect_id + 1));
    world->effect_list[effect_id].name = NULL;
    return fclose(stream);
}
