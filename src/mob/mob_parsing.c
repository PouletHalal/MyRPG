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

int set_damage(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atof(split[1]) < 0.) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_stat.damage = atof(split[1]);
    free_array(split);
    return 0;
}

int set_defense(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atof(split[1]) < 0.) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_stat.defense = atof(split[1]);
    free_array(split);
    return 0;
}

int set_health(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atof(split[1]) < 0.) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_stat.health = atof(split[1]);
    entity->comp_stat.max_health = entity->comp_stat.health;
    free_array(split);
    return 0;
}

int set_health_regen(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atof(split[1]) < 0.) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_stat.health_regen = atof(split[1]);
    free_array(split);
    return 0;
}
