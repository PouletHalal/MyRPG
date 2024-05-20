/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** init_mob
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"
#include "mob.h"

int set_does_damage(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_stat.do_respawn = GET_BOOL(split[1]);
    free_array(split);
    return 0;
}

int set_does_respawn(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_stat.do_respawn = GET_BOOL(split[1]);
    free_array(split);
    return 0;
}

int set_does_follow(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_mob.does_follow = GET_BOOL(split[1]);
    entity->comp_position.can_move = entity->comp_mob.does_follow;
    free_array(split);
    return 0;
}

static int get_arg(char **split, world_t *world, entity_t *entity, char *line)
{
    for (int i = 0; MOB_ARGS[i].name != NULL; i++) {
        if (strcmp(split[0], MOB_ARGS[i].name) == 0) {
            free_array(split);
            return MOB_ARGS[i].ptr(world, entity, line);
        }
    }
    free_array(split);
    return 0;
}

static void read_mob(world_t *world, char *filename)
{
    FILE *stream = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    entity_t *entity = &world->entity[find_empty(world)];
    char **split = NULL;

    if (test_open(stream, filename) == -1)
        return;
    entity->comp_mob.is_alive = true;
    while (getline(&line, &len, stream) > 0) {
        if (line[0] == '\0' || line[0] == '\n')
            break;
        split = my_str_to_word_array(line, "=\n ");
        entity->mask |= COMP_STAT | COMP_MOB | COMP_POSITION;
        if (get_arg(split, world, entity, line) == 84) {
            entity->mask = COMP_NONE;
            break;
        }
    }
    fclose(stream);
}

void read_mobconf(world_t *world)
{
    FILE *stream = fopen(MOB_CONF, "r");
    char *line = NULL;
    size_t len = 0;

    if (test_open(stream, MOB_CONF) == -1)
        return;
    while (getline(&line, &len, stream) > 0) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (line[0] == '\0')
            break;
        read_mob(world, line);
    }
    fclose(stream);
}
