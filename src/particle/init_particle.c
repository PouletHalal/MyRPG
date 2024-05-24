/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** init_particle
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "particle.h"
#include "temp.h"
#include "player.h"
#include "error_handling.h"
#include "particle.h"

static int get_arg(char **split, world_t *world, entity_t *entity, char *line)
{
    for (int i = 0; PART_ARGS[i].name != NULL; i++) {
        if (strcmp(split[0], PART_ARGS[i].name) == 0) {
            free_array(split);
            return PART_ARGS[i].ptr(world, entity, line);
        }
    }
    free_array(split);
    return 0;
}

static void init_rect(entity_t *entity)
{
    if (entity->comp_particle.particles == NULL) {
        entity->mask = COMP_NONE;
        return;
    }
    entity->comp_particle.rectangle = sfRectangleShape_create();
    sfRectangleShape_setSize(entity->comp_particle.rectangle,
    entity->comp_particle.size);
    sfRectangleShape_setFillColor(entity->comp_particle.rectangle,
    entity->comp_particle.color);
}

static void read_part(world_t *world, char *filename)
{
    FILE *stream = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    entity_t *entity = &world->entity[find_empty(world)];
    char **split = NULL;

    if (test_open(stream, filename) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        if (line[0] == '\0' || line[0] == '\n')
            break;
        split = my_str_to_word_array(line, "=\n ");
        entity->mask |= COMP_PARTICLE;
        if (get_arg(split, world, entity, line) == 84) {
            entity->mask = COMP_NONE;
            break;
        }
    }
    init_rect(entity);
    fclose(stream);
}

void read_partconf(world_t *world)
{
    FILE *stream = fopen(PART_CONF, "r");
    char *line = NULL;
    size_t len = 0;

    if (test_open(stream, PART_CONF) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (line[0] == '\0')
            break;
        read_part(world, line);
    }
    fclose(stream);
}
