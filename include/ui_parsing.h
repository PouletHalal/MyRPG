/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** ui_parsing
*/

#ifndef UI_PARSING_H_
    #define UI_PARSING_H_

    #include "npcs.h"

int set_hover(world_t *world, entity_t *entity, char *args);
int set_ui_mask(world_t *world, entity_t *entity, char *args);
int set_base_anim(world_t *world, entity_t *entity, char *args);
int set_next_mask(world_t *world, entity_t *entity, char *args);
int set_button_name(world_t *world, entity_t *entity, char *args);
int set_button_pos(world_t *world, entity_t *entity, char *args);

static const ptr_func_t UI_FLAGS[] = {
    {"base_anim", &set_base_anim},
    {"hover", &set_hover},
    {"ui_mask", &set_ui_mask},
    {"next_mask", &set_next_mask},
    {"name", &set_button_name},
    {"pos", &set_button_pos},
    {NULL, NULL}
};



#endif /* !UI_PARSING_H_ */
