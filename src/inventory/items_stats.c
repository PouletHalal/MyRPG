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

int set_health(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    item->stats.health = atof(split[1]);
    item->stats.max_health = item->stats.health;
    free_array(split);
    return 0;
}
