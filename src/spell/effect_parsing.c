/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** effect_parsing
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "temp.h"
#include "rendering.h"
#include "player.h"
#include "error_handling.h"
#include "effect_parsing.h"

int set_effect_name(world_t *world, effect_t *effect, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    effect->name = strdup(split[1]);
    effect->effect_type = get_effect_id(split[1]);
    free_array(split);
    return 0;
}

int set_effect_value(world_t *world, effect_t *effect, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    effect->value = atoi(split[1]);
    free_array(split);
    return 0;
}

int set_base_tick_cooldown(world_t *world, effect_t *effect, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    effect->base_tick_cooldown = atoi(split[1]);
    free_array(split);
    return 0;
}

int set_duration(world_t *world, effect_t *effect, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    effect->duration = atoi(split[1]);
    free_array(split);
    return 0;
}
