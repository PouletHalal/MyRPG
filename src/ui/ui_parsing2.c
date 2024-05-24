/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** ui_parsing2
*/


#include <stdlib.h>
#include <string.h>
#include "ui_parsing.h"
#include "world.h"
#include "error_handling.h"
#include "ui.h"

int set_button_pos(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\t\n");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 2, "Invalid arguments ->", args);
    temp = my_str_to_word_array(split[1], ", \n\t");
    if (temp == NULL || temp[1] == NULL)
        return int_display_and_return(84, 2, "Invalid arguments ->", args);
    entity->mask |= COMP_POSITION;
    init_comp_position(entity, (sfVector2f) {atof(temp[0]), atof(temp[1])}, 0);
    return 0;   
}
