/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** ui_parsing
*/

#include <stdlib.h>
#include <string.h>
#include "ui_parsing.h"
#include "world.h"
#include "error_handling.h"
#include "ui.h"

int set_hover(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\t\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid arguments ->", args);
    entity->mask |= COMP_UI;
    entity->comp_ui.hover = &world->animations[get_anim_id(world, split[1])];
    return 0;
}

int set_ui_mask(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\t\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid arguments ->", args);
    entity->mask |= COMP_UI;
    entity->comp_ui.ui_mask |= get_ui_mask(split[1]);
    return 0;
}

int set_base_anim(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\t\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid arguments ->", args);
    entity->mask |= COMP_UI;
    entity->comp_ui.base = &world->animations[get_anim_id(world, split[1])];
    set_idle(world, entity, args);
    return 0;
}

int set_next_mask(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\t\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid arguments ->", args);
    entity->mask |= COMP_UI;
    entity->comp_ui.next_mask = get_ui_mask(split[1]);
    return 0;
}

int set_button_name(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\t\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid arguments ->", args);
    entity->mask |= COMP_UI;
    entity->comp_ui.name = strdup(split[1]);
    return 0;
}
