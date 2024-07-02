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

int set_part_rate(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atof(split[1]) < 0) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_particle.spawn_rate = atof(split[1]);
    free_array(split);
    return 0;
}

int set_size(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    for (int i = 1; i < 3; ++i)
        if (split[i] == NULL)
            return int_display_and_return(84, 3, "Invalid arg: ", args, "\n");
    entity->comp_particle.size.x = atof(split[1]);
    entity->comp_particle.size.y = atof(split[2]);
    free_array(split);
    return 0;
}
