/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** mob_parsing4
*/

#include <stdlib.h>
#include <string.h>
#include "error_handling.h"
#include "mob.h"
#include "temp.h"
#include "ecs.h"

int set_exp_loot(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atof(split[1]) < 0.) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_stat.exp_loot = atof(split[1]);
    free_array(split);
    return 0;
}
