/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** item_stats2
*/

#include <string.h>
#include <stdlib.h>
#include "inventory.h"
#include "error_handling.h"
#include "world.h"


int set_item_mana(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    item->stats.mana_max = atof(split[1]);
    item->stats.mana = atof(split[1]);
    free_array(split);
    return 0;
}

int set_item_xp(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    item->stats.exp = atof(split[1]);
    free_array(split);
    return 0;
}
