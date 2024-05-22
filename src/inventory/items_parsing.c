/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** item_parsing
*/

#include <string.h>
#include <stdlib.h>
#include "inventory.h"
#include "error_handling.h"
#include "world.h"

int get_mask_from_str(char *str)
{
    for (int i = 0; ITEM_TYPES_NAMES[i].name != NULL; i++) {
        if (strcmp(str, ITEM_TYPES_NAMES[i].name) == 0)
            return ITEM_TYPES_NAMES[i].mask;
    }
    for (int i = 0; EQUIP_NAMES[i].name != NULL; i++) {
        if (strcmp(str, EQUIP_NAMES[i].name) == 0)
            return EQUIP_NAMES[i].mask;
    }
    return 0;
}

int set_type(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");
    char **temp = NULL;

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    temp = my_str_to_word_array(split[1], ",\n\t");
    if (temp == NULL || temp[0] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    item->type_mask |= get_mask_from_str(temp[0]);
    if (item->type_mask == 0)
        return int_display_and_return(84, 3, "Invalid mask :", args, "\n");
    return 0;
}

int set_name(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");
    char **temp = NULL;
    sfText *text = sfText_create();

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    temp = my_str_to_word_array(args, "\"");
    item->tooltip.name = strdup(temp[1]);
    item->tooltip.name_txt = text;
    sfText_setString(text, item->tooltip.name);
    sfText_setCharacterSize(text, 20);
    free_array(split);
    return 0;
}

int set_description(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");
    char **temp = NULL;
    sfText *text = sfText_create();

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    temp = my_str_to_word_array(args, "\"");
    item->tooltip.description = strdup(temp[1]);
    item->tooltip.description_txt = text;
    sfText_setString(text, item->tooltip.description);
    sfText_setCharacterSize(text, 20);
    free_array(split);
    return 0;
}

int set_animation_id(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    item->animation_id = get_anim_id(world, split[1]);
    if (item->animation_id == -1) {
        item->animation_id = 0;
        int_display_and_return(84, 3, "Invalid animation id :", args, "\n"
        );
    }
    free_array(split);
    return 0;
}
