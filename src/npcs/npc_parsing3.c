/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** npc_parsing3
*/

#include <stdlib.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"
#include "dialogs.h"
#include "ecs.h"
#include "player.h"

int set_input(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    char **temp = NULL;

    entity->comp_dialog.camera_focus = true;
    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(split[1], ", \t\n");
    if (temp == NULL || temp[0] == NULL || temp[1] == NULL || temp[2] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    free_array(split);
    entity->comp_dialog.need_input = GET_BOOL(temp[0]);
    entity->comp_dialog.detection_area.x = atof(temp[1]);
    entity->comp_dialog.detection_area.y = atof(temp[2]);
    free_array(temp);
    if (entity->comp_dialog.detection_area.x < 0 ||
        entity->comp_dialog.detection_area.y < 0)
        return int_display_and_return(84, 3, "Invalid Area: ", args, "\n");
    return 0;
}

int set_camera_focus(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_dialog.camera_focus = GET_BOOL(split[1]);
    return 0;
}

int gives_item(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(args, "\"");
    entity->comp_npc.gives_item = true;
    entity->comp_npc.item_id = get_item_id(world->item_list, temp[1]);
    return 0;
}

int gives_item_dialog_id(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_npc.gives_item_dialog_id = atoi(split[1]);
    if (entity->comp_npc.gives_item_dialog_id < 0) {
        entity->comp_npc.gives_item_dialog_id = 0;
        return int_display_and_return(84, 3, "Invalid dialog id: ",
        split[1], "\n");
    }
    return 0;
}

int gives_item_sentence_id(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_npc.gives_item_sentence_id = atoi(split[1]);
    if (entity->comp_npc.gives_item_sentence_id < 0) {
        entity->comp_npc.gives_item_sentence_id = 0;
        return int_display_and_return(84, 3, "Invalid dialog id: ",
        split[1], "\n");
    }
    return 0;
}
