/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** animation_parsing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"

int set_anim_name(animation_t *anim, char *args)
{
    char **split = my_str_to_word_array(args, "=\n ");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid name :", args);
    anim->name = strdup(split[1]);
    return 0;
}

int set_base_rect(animation_t *anim, char *args)
{
    char **split = my_str_to_word_array(args, "=\n ");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid base rect :", args);
    temp = my_str_to_word_array(split[1], ",");
    if (temp == NULL || len_array(temp) != 4)
        return int_display_and_return(84, 2, "Invalid base rect :", args);
    anim->base_text_rect = (sfIntRect) {atoi(temp[0]), atoi(temp[1]),
        atoi(temp[2]), atoi(temp[3])};
    return 0;
}

int set_frame_count(animation_t *anim, char *args)
{
    char **split = my_str_to_word_array(args, "=\n ");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid frame count :", args);
    anim->frame_count = atoi(split[1]);
    if (anim->frame_count <= 0)
        return int_display_and_return(84, 2, "Invalid frame count :", args);
    return 0;
}

int set_frame_size(animation_t *anim, char *args)
{
    char **split = my_str_to_word_array(args, "=\n ");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid frame size :", args);
    temp = my_str_to_word_array(split[1], ",");
    if (temp == NULL || len_array(temp) != 2)
        return int_display_and_return(84, 2, "Invalid frame size :", args);
    anim->frame_size = (sfVector2i) {atoi(temp[0]), atoi(temp[1])};
    return 0;
}

int set_anim_scale(animation_t *anim, char *args)
{
    char **split = my_str_to_word_array(args, "=\n ");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid scale :", args);
    temp = my_str_to_word_array(split[1], ",");
    if (temp == NULL || len_array(temp) != 2)
        return int_display_and_return(84, 2, "Invalid scale :", args);
    anim->scale = (sfVector2f) {atof(temp[0]), atof(temp[1])};
    return 0;
}

