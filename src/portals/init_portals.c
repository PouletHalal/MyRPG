/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_portals
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"
#include "portals.h"

static int get_arg(char **split, world_t *world, entity_t *entity, char *line)
{
    if (split == NULL || split[0] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid line: ", line, "\n");
    }
    for (int i = 0; PORTAL_FLAGS[i].name != NULL; i++) {
        if (strcmp(split[0], PORTAL_FLAGS[i].name) == 0 &&
            PORTAL_FLAGS[i].ptr != NULL) {
            free_array(split);
            return PORTAL_FLAGS[i].ptr(world, entity, line);
        }
    }
    free_array(split);
    return 0;
}

static void init_portal(world_t *world, char *filename)
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
        entity->mask |= COMP_PORTAL;
        if (get_arg(split, world, entity, line) == 84) {
            entity->mask = COMP_NONE;
            break;
        }
    }
    fclose(stream);
}

void read_portalconf(world_t *world)
{
    FILE *stream = fopen(PORTAL_CONF, "r");
    char *line = NULL;
    size_t len = 0;

    if (test_open(stream, PORTAL_CONF) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (line[0] == '\0')
            break;
        init_portal(world, line);
    }
    fclose(stream);
}
