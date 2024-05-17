/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** npc_parsing2
*/

#include <stdlib.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"
#include "dialogs.h"
#include "ecs.h"
#include "player.h"

int set_font(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    sfFont *font = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    font = sfFont_createFromFile(split[1]);
    if (font == NULL)
        return int_display_and_return(84, 3, "Invalid font: ", split[1], "\n");
    entity->comp_dialog.font = font;
    entity->comp_dialog.sftext = sfText_create();
    sfText_setFont(entity->comp_dialog.sftext, font);
    return 0;
}

int set_is_displayed(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_dialog.is_displayed = GET_BOOL(split[1]);
    entity->comp_dialog.current_dialog = ((int) GET_BOOL(split[1])) - 1;
    return 0;
}

int set_player_movement(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_dialog.freeze_player = GET_BOOL(split[1]);
    return 0;
}

int set_loop(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    entity_t *player = &world->entity[find_comp(world, COMP_POSITION)];

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_dialog.does_loop = GET_BOOL(split[1]);
    player->comp_position.can_move = !entity->comp_dialog.freeze_player;
    return 0;
}

int set_box_scale(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    sfVector2f scale = {0};
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(split[1], " ,\n\t");
    if (temp == NULL || temp[0] == NULL || temp[1] == NULL)
        return int_display_and_return(84, 3, "Invalid scale:", split[1], "\n");
    scale.x = atof(temp[0]);
    scale.y = atof(temp[1]);
    if (entity->comp_dialog.box == NULL)
        return int_display_and_return(84, 3, "No box to scale: ", args, "\n");
    sfSprite_setScale(entity->comp_dialog.box, scale);
    return 0;
}
