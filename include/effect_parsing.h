/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** effect_parsing
*/

#ifndef EFFECT_PARSING_H_
    #define EFFECT_PARSING_H_

    #include "world.h"

int set_effect_name(world_t *world, effect_t *effect, char *args);
int set_effect_value(world_t *world, effect_t *effect, char *args);
int set_base_tick_cooldown(world_t *world, effect_t *effect, char *args);
int set_duration(world_t *world, effect_t *effect, char *args);

typedef struct effect_ptr_func_s {
    char *name;
    int (*ptr) (world_t *world, effect_t *effect, char *args);
} effect_ptr_func_t;


static const effect_ptr_func_t EFFECT_FLAG[] =
{
    {"name", &set_effect_name},
    {"value", &set_effect_value},
    {"base_tick_cooldown", &set_base_tick_cooldown},
    {"duration", &set_duration},
    {NULL, NULL},
};

#endif /* !EFFECT_PARSING_H_ */
