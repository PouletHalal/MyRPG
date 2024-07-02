/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** part_parsing
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"
#include "particle.h"

int set_angles(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    for (int i = 1; i < 3; ++i)
        if (split[i] == NULL || atoi(split[i]) < 0)
            return int_display_and_return(84, 3, "Invalid arg: ", args, "\n");
    entity->comp_particle.angles[0] = atoi(split[1]);
    entity->comp_particle.angles[1] = atoi(split[2]);
    free_array(split);
    return 0;
}

int set_part_speed(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    for (int i = 1; i < 3; ++i)
        if (split[i] == NULL || atof(split[i]) < 0)
            return int_display_and_return(84, 3, "Invalid arg: ", args, "\n");
    entity->comp_particle.speed[0] = atof(split[1]);
    entity->comp_particle.speed[1] = atof(split[2]);
    free_array(split);
    return 0;
}

int set_lifespan(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atoi(split[1]) < 0) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_particle.lifespan = atoi(split[1]);
    free_array(split);
    return 0;
}

int set_spawn(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    for (int i = 1; i < 5; ++i)
        if (split[i] == NULL)
            return int_display_and_return(84, 3, "Invalid arg: ", args, "\n");
    entity->comp_particle.spawn_rect.left = atoi(split[1]);
    entity->comp_particle.spawn_rect.top = atoi(split[2]);
    entity->comp_particle.spawn_rect.width = atoi(split[3]);
    entity->comp_particle.spawn_rect.height = atoi(split[4]);
    free_array(split);
    return 0;
}

int set_world(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atoi(split[1]) < 0) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_particle.world = atoi(split[1]);
    free_array(split);
    return 0;
}
