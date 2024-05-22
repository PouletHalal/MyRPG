/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** item_stats
*/

#include <string.h>
#include <stdlib.h>
#include "inventory.h"
#include "error_handling.h"
#include "world.h"

int set_item_regen(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    item->stats.health_regen = atof(split[1]);
    if (item->stats.health_regen < 0)
        return int_display_and_return(84, 3, "Invalid regen:", split[1], "\n");
    free_array(split);
    return 0;
}

int set_item_attack(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    item->stats.damage = atof(split[1]);
    if (item->stats.damage < 0)
        return int_display_and_return(84, 3, "Invalid dmg: ", split[1], "\n");
    free_array(split);
    return 0;
}

int set_item_defense(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    item->stats.defense = atof(split[1]);
    if (item->stats.defense < 0)
        return int_display_and_return(84, 3, "Invalid def: ", split[1], "\n");
    free_array(split);
    return 0;
}

int set_item_health(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    item->stats.health = atof(split[1]);
    item->stats.max_health = item->stats.health;
    free_array(split);
    return 0;
}

int set_drop_rate(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    item->drop_rate = atof(split[1]);
    if (item->drop_rate <= 0)
        return int_display_and_return(84, 3, "Invalid drop rate:", split[1], "\n");
    free_array(split);
    return 0;
}
