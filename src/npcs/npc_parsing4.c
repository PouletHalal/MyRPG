/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** npc_parsing4
*/

#include <stdlib.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"
#include "dialogs.h"
#include "ecs.h"
#include "player.h"

int set_key_item_to_talk(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(args, "\"");
    entity->comp_npc.need_key_item_to_talk = true;
    entity->comp_npc.key_item_to_talk_id = get_item_id(world->item_list,
    temp[1]);
    free_array(temp);
    free_array(split);
    return 0;
}

int set_key_item_to_drop(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(args, "\"");
    entity->comp_npc.need_key_item_to_drop = true;
    entity->comp_npc.key_item_to_drop_id = get_item_id(world->item_list,
    temp[1]);
    free_array(temp);
    free_array(split);
    return 0;
}

int set_takes_item(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(args, "\"");
    entity->comp_npc.takes_item = true;
    free_array(temp);
    free_array(split);
    return 0;
}

int takes_item_dialog_id(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_npc.takes_item_dialog_id = atoi(split[1]);
    if (entity->comp_npc.takes_item_dialog_id < 0) {
        entity->comp_npc.takes_item_dialog_id = 0;
        return int_display_and_return(84, 3, "Invalid dialog id: ",
        split[1], "\n");
    }
    return 0;
}

int takes_item_sentence_id(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_npc.takes_item_sentence_id = atoi(split[1]);
    if (entity->comp_npc.takes_item_sentence_id < 0) {
        entity->comp_npc.takes_item_sentence_id = 0;
        return int_display_and_return(84, 3, "Invalid dialog id: ",
        split[1], "\n");
    }
    return 0;
}
