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
#include "player.h"

int set_part_color(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    for (int i = 1; i < 5; ++i)
        if (split[i] == NULL || atoi(split[i]) < 0 || atoi(split[i]) > 255)
            return int_display_and_return(84, 3, "Invalid arg: ", args, "\n");
    entity->comp_particle.color.r = atoi(split[1]);
    entity->comp_particle.color.g = atoi(split[2]);
    entity->comp_particle.color.b = atoi(split[3]);
    entity->comp_particle.color.a = atoi(split[4]);
    free_array(split);
    return 0;
}

int set_max_part(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atoi(split[1]) < 0) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_particle.max_particles = atoi(split[1]);
    entity->comp_particle.particles = calloc(atoi(split[1]),
    sizeof(particle_t));
    free_array(split);
    if (entity->comp_particle.particles == NULL) {
        entity->comp_particle.max_particles = 0;
        return int_display_and_return(84, 3, "Calloc error: ", args, "\n");
    }
    return 0;
}

int set_need_center(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    int player = find_comp(world, COMP_PLAYER);

    if (split == NULL || split[1] == NULL || player == -1) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_particle.is_entity_centered = GET_BOOL(split[1]);
    entity->comp_particle.entity = player;
    free_array(split);
    return 0;
}

int set_need_move(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    if (GET_BOOL(split[1]))
        entity->comp_particle.condition_mask |= PART_MOVE;
    free_array(split);
    return 0;
}

int set_need_rain(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    if (GET_BOOL(split[1]))
        entity->comp_particle.condition_mask |= PART_RAIN;
    free_array(split);
    return 0;
}
