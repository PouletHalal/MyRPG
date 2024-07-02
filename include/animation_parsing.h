/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** animation_parsing
*/

#ifndef ANIMATION_PARSING_H_
    #define ANIMATION_PARSING_H_

    #include "world.h"

typedef struct anim_ptr_func {
    char *name;
    int (*ptr)(animation_t *anim, char *args);
} anim_ptr_func_t;

int set_anim_name(animation_t *anim, char *args);
int set_base_rect(animation_t *anim, char *args);
int set_frame_count(animation_t *anim, char *args);
int set_frame_size(animation_t *anim, char *args);
int set_frame_rate(animation_t *anim, char *args);
int set_anim_scale(animation_t *anim, char *args);
int set_texture_name(animation_t *anim, char *args);

anim_ptr_func_t ANIM_FLAGS[] =
{
    {"name", &set_anim_name},
    {"base_rect", &set_base_rect},
    {"frame_count", &set_frame_count},
    {"frame_size", &set_frame_size},
    {"frame_rate", &set_frame_rate},
    {"scale", &set_anim_scale},
    {"filename", &set_texture_name},
    {NULL, NULL},
};

#endif /* !ANIMATION_PARSING_H_ */
