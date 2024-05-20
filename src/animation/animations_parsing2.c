/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** animation_parsing2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"


int set_frame_rate(animation_t *anim, char *args)
{
    char **split = my_str_to_word_array(args, "=\n ");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid frame rate :", args);
    anim->frame_rate = atoi(split[1]);
    if (anim->frame_rate <= 0)
        return int_display_and_return(84, 2, "Invalid frame rate :", args);
    return 0;
}

int set_texture_name(animation_t *anim, char *args)
{
    char **split = my_str_to_word_array(args, "=\n ");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid texture name :", args);
    anim->filename = strdup(split[1]);
    return 0;
}
