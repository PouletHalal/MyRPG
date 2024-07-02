/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** mob_parsing
*/

#include <stdlib.h>
#include <string.h>
#include "error_handling.h"
#include "mob.h"
#include "ecs.h"

int set_delay(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atof(split[1]) < 0.) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_stat.invinsibility_frames = atof(split[1]);
    free_array(split);
    return 0;
}

int set_speed(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL ||
    atof(split[1]) < 0. || atof(split[1]) > 32.) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_mob.speed = atof(split[1]);
    free_array(split);
    return 0;
}

int set_does_take_damage(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_mob.does_follow = GET_BOOL(split[1]);
    free_array(split);
    return 0;
}

int set_range(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atof(split[1]) < 0.) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_mob.range = atof(split[1]);
    free_array(split);
    return 0;
}

int set_faction(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL ||
    atoi(split[1]) < 0 || atoi(split[1]) > MAX_FACTION) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_stat.faction = atoi(split[1]);
    free_array(split);
    return 0;
}
