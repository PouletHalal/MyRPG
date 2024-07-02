/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** spell_parsing2
*/

#include <stdio.h>
#include <stdlib.h>
#include "temp.h"
#include "player.h"
#include "npcs.h"
#include "dialogs.h"
#include "error_handling.h"

int set_spell_speed(world_t *world, comp_spell_t *spell, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    spell->speed = atof(split[1]);
    free_array(split);
    return 0;
}

int set_spell_effect(world_t *world, comp_spell_t *spell, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    spell->effect_index = get_effect_id(split[1]);
    free_array(split);
    return 0;
}

int set_spell_cost(world_t *world, comp_spell_t *spell, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    spell->cost = atof(split[1]);
    free_array(split);
    return 0;
}
