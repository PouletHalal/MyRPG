/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_ui
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp.h"
#include "ui_parsing.h"
#include "lib.h"
#include "ui.h"
#include "error_handling.h"

int get_ui_mask(char *name)
{
    for (int i = 0; UI_MASKS_NAMES[i].name != NULL; i++) {
        if (strcmp(name, UI_MASKS_NAMES[i].name) == 0)
            return UI_MASKS_NAMES[i].mask;
    }
    return 0;
}

static int get_ui_arg(world_t *world, entity_t *entity, char **split,
    char *line)
{
    for (int i = 0; UI_FLAGS[i].name != NULL; i++) {
        if (strcmp(split[0], UI_FLAGS[i].name) == 0 &&
            UI_FLAGS[i].ptr != NULL) {
            free_array(split);
            return UI_FLAGS[i].ptr(world, entity, line);
        }
    }
    free_array(split);
    return 0;
}

static void init_button(world_t *world, char *filename)
{
    FILE *stream = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    int free_slot = find_empty(world);
    entity_t *entity = &world->entity[free_slot];
    char **split = NULL;

    if (test_open(stream, filename) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        if (line[0] == '\0' || line[0] == '\n')
            break;
        split = my_str_to_word_array(line, "=\n ");
        entity->mask |= COMP_DIALOG;
        if (get_ui_arg(world, entity, split, line) == 84) {
            entity->mask = COMP_NONE;
            break;
        }
    }
    fclose(stream);
}

void read_ui_conf(world_t *world)
{
    FILE *stream = fopen(BUTTON_CONF, "r");
    char *line = NULL;
    size_t len = 0;

    if (test_open(stream, BUTTON_CONF) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (line[0] == '\0')
            break;
        init_button(world, line);
    }
    fclose(stream);
}
