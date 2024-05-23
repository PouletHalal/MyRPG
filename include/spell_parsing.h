/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** spell_parsing
*/

#ifndef SPELL_PARSING_H_
    #define SPELL_PARSING_H_

    #include "world.h"

int set_spell_anim(world_t *world, comp_spell_t *spell, char *args);
int set_spell_target(world_t *world, comp_spell_t *spell, char *args);
int set_spell_move_type(world_t *world, comp_spell_t *spell, char *args);
int set_spell_damage(world_t *world, comp_spell_t *spell, char *args);
int set_spell_duration(world_t *world, comp_spell_t *spell, char *args);
int set_spell_speed(world_t *world, comp_spell_t *spell, char *args);
int set_spell_effect(world_t *world, comp_spell_t *spell, char *args);

typedef struct spell_ptr_func_s {
    char *name;
    int (*ptr) (world_t *world, comp_spell_t *spell, char *args);
} spell_ptr_func_t;

spell_ptr_func_t SPELL_FLAGS[] =
{
    {"animation_id", &set_spell_anim},
    {"target", &set_spell_target},
    {"move_type", &set_spell_move_type},
    {"damage", &set_spell_damage},
    {"duration", &set_spell_duration},
    {"speed", &set_spell_speed},
    {"effect", &set_spell_effect},
    {NULL, NULL},
};

#endif /* !SPELL_PARSING_H_ */
