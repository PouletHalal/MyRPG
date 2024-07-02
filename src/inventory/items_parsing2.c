/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** item_parsing2
*/

#include <string.h>
#include <stdlib.h>
#include "inventory.h"
#include "world.h"
#include "error_handling.h"

int set_tooltip(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    item->tooltip.sprite.texture = sfTexture_createFromFile(split[1], NULL);
    if (item->tooltip.sprite.texture == NULL)
        return int_display_and_return(84, 3, "Invalid texture :", args, "\n");
    item->tooltip.sprite.sprite = sfSprite_create();
    sfSprite_setTexture(item->tooltip.sprite.sprite,
    item->tooltip.sprite.texture, sfTrue);
    free_array(split);
    return 0;
}

int set_scale(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");
    char **temp = NULL;

    if (item->tooltip.sprite.sprite == NULL)
        return int_display_and_return(84, 3, "No texture set for tooltip :",
        args, "\n");
    if (split == NULL || split[0] == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    temp = my_str_to_word_array(split[1], ",\n\t");
    if (temp == NULL || temp[0] == NULL || temp[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args :", args, "\n");
    item->tooltip.sprite.scale = (sfVector2f) {atof(temp[0]), atof(temp[1])};
    free_array(split);
    free_array(temp);
    return 0;
}

int set_item_font(world_t *world, comp_item_t *item, char *args)
{
    char **split = my_str_to_word_array(args, "= \n\t");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    item->tooltip.font = sfFont_createFromFile(split[1]);
    if (item->tooltip.font == NULL)
        return int_display_and_return(84, 3, "Invalid font: ", split[1], "\n");
    if (!item->tooltip.name_txt || !item->tooltip.description_txt)
        return int_display_and_return(84, 3, "No name or description set :",
        args, "\n");
    sfText_setFont(item->tooltip.name_txt, item->tooltip.font);
    sfText_setFont(item->tooltip.description_txt, item->tooltip.font);
    return 0;
}
