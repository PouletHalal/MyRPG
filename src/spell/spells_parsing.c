/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** spells_parsing
*/

#include <stdio.h>
#include <stdlib.h>
#include "temp.h"
#include "player.h"
#include "npcs.h"
#include "dialogs.h"
#include "error_handling.h"

int set_spell_anim(world_t *world, comp_spell_t *spell, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    spell->index = get_anim_id(world, split[1]);
    spell->animation = &world->animations[spell->index];
    free_array(split);
    return 0;
}

int set_spell_target(world_t *world, comp_spell_t *spell, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    spell->target = get_target_id(split[1]);
    free_array(split);
    return 0;
}

int set_spell_move_type(world_t *world, comp_spell_t *spell, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    spell->move_type = get_move_id(split[1]);
    free_array(split);
    return 0;
}

int set_spell_damage(world_t *world, comp_spell_t *spell, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    spell->damage = atof(split[1]);
    free_array(split);
    return 0;
}

int set_spell_duration(world_t *world, comp_spell_t *spell, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    spell->duration = atof(split[1]);
    free_array(split);
    return 0;
}

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
