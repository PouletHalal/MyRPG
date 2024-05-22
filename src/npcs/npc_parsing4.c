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
    entity->comp_npc.key_item_to_talk_id = get_item_id(world->item_list, temp[1]);
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
    entity->comp_npc.key_item_to_drop_id = get_item_id(world->item_list, temp[1]);
    free_array(temp);
    free_array(split);
    return 0;
}


