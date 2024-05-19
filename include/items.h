/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** items
*/

#ifndef ITEMS_H_
    #define ITEMS_H_

    #include "npcs.h"

typedef struct item_ptr_func {
    char *name;
    int (*ptr)(world_t *world, comp_item_t *item, char *args);
} item_ptr_func_t;


int set_description(world_t *world, comp_item_t *item, char *args);
int set_name(world_t *world, comp_item_t *item, char *args);
int set_type(world_t *world, comp_item_t *item, char *args);
int set_animation_id(world_t *world, comp_item_t *item, char *args);


item_ptr_func_t ITEM_FLAGS[] =
{
    {"type", &set_type},
    {"name", &set_name},
    {"description", &set_description},
    {"animation_id", &set_animation_id},
    {NULL, NULL}
};


#endif /* !ITEMS_H_ */
