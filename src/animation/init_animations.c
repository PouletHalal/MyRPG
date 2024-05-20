/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_animations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"
#include "animation_parsing.h"

static bool is_valid_line(char *line)
{
    if (line == NULL)
        return false;
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
    if (line[0] == '\0' || line[0] == '\n')
        return false;
    return true;
}

static int get_anim_arg(animation_t *anim, char **split, char *args)
{
    for (int i = 0; ANIM_FLAGS[i].name != NULL; ++i) {
        if (strcmp(ANIM_FLAGS[i].name, split[0]) == 0)
            return ANIM_FLAGS[i].ptr(anim, args);
    }
    return 0;
}

static void init_anim(animation_t *anim, char *filename)
{
    FILE *stream = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    char **split = NULL;

    if (test_open(stream, filename) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        if (is_valid_line(line) == false)
            break;
        split = my_str_to_word_array(line, "=\n ");
        if (get_anim_arg(anim, split, line)) {
            *anim = (animation_t) {0};
        }
    }
    fclose(stream);
}

void read_animconf(world_t *world)
{
    FILE *stream = fopen(ANIM_CONF, "r");
    char *line = NULL;
    size_t len = 0;
    int nb_anim = 0;

    if (openning_and_reading(stream, ANIM_CONF, &line) == 84)
        return;
    nb_anim = atoi(line);
    world->animations = calloc(nb_anim + 1, sizeof(animation_t));
    for (int id = 0; getline(&line, &len, stream) > 0; ++id) {
        if (!is_valid_line(line))
            break;
        world->animations[id].index = id;
        init_anim(&world->animations[id], line);
    }
}
