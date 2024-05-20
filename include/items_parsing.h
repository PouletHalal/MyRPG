/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** items_parsing
*/

#ifndef ITEMS_PARSING_H_
    #define ITEMS_PARSING_H_

    #include "world.h"

typedef struct item_ptr_func {
    char *name;
    int (*ptr)(world_t *world, comp_item_t *item, char *args);
} item_ptr_func_t;


int set_description(world_t *world, comp_item_t *item, char *args);
int set_name(world_t *world, comp_item_t *item, char *args);
int set_type(world_t *world, comp_item_t *item, char *args);
int set_animation_id(world_t *world, comp_item_t *item, char *args);
int set_tooltip(world_t *world, comp_item_t *item, char *args);
int set_scale(world_t *world, comp_item_t *item, char *args);
int set_item_font(world_t *world, comp_item_t *item, char *args);
int set_health(world_t *world, comp_item_t *item, char *args);

item_ptr_func_t ITEM_FLAGS[] =
{
    {"type", &set_type},
    {"name", &set_name},
    {"description", &set_description},
    {"animation_id", &set_animation_id},
    {"tooltip_box", &set_tooltip},
    {"tooltip_scale", &set_scale},
    {"font", &set_item_font},
    {"healing", &set_health},
    {NULL, NULL}
};

#endif /* !ITEMS_PARSING_H_ */
