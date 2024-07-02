/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** portal_parsing
*/

#include <stdlib.h>
#include <stdio.h>
#include "temp.h"
#include "error_handling.h"

int set_origin_id(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    int nb_maps = 0;

    for (nb_maps = 0; world->map_list[nb_maps] != NULL; nb_maps++);
    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_portal.origin_id = atoi(split[1]);
    if (entity->comp_portal.origin_id < 0 ||
        entity->comp_portal.origin_id >= nb_maps)
        return int_display_and_return(84, 3, "Invalid origin id: ",
        split[1], "\n");
    return 0;
}

int set_origin_pos(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n\t");
    char **temp = NULL;
    sfVector2f pos = {0};

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(split[1], ", \t");
    if (temp == NULL || temp[0] == NULL || temp[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    pos = (sfVector2f) {atof(temp[0]), atof(temp[1])};
    if (pos.x < 0 || pos.y < 0 || pos.x >=
        world->map_list[entity->comp_portal.origin_id]->maps->size.x ||
        pos.y >= world->map_list[entity->comp_portal.origin_id]->maps->size.y)
        return int_display_and_return(84, 3, "Invalid pos: ", split[1], "\n");
    init_comp_position(entity, (sfVector2f) {atof(temp[0]), atof(temp[1])},
    entity->comp_portal.origin_id);
}

int set_destination_id(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    int nb_maps = 0;

    for (nb_maps = 0; world->map_list[nb_maps] != NULL; nb_maps++);
    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_portal.dest_id = atoi(split[1]);
    if (entity->comp_portal.dest_id < 0 ||
        entity->comp_portal.dest_id >= nb_maps)
        return int_display_and_return(84, 3, "Invalid origin id: ",
        split[1], "\n");
    return 0;
}

int set_destination_pos(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n\t");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(split[1], ", \t");
    if (temp == NULL || temp[0] == NULL || temp[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_portal.dest_pos = (sfVector2f) {atof(temp[0]), atof(temp[1])};
    if (entity->comp_portal.dest_pos.x < 0 ||
        entity->comp_portal.dest_pos.y < 0 ||
        entity->comp_portal.dest_pos.x >=
        world->map_list[entity->comp_portal.dest_id]->maps->size.x ||
        entity->comp_portal.dest_pos.y >=
        world->map_list[entity->comp_portal.dest_id]->maps->size.y)
        return int_display_and_return(84, 3, "Invalid destination pos: ",
        split[1], "\n");
    return 0;
}

int set_hitbox(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n\t");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(split[1], ", \t");
    if (temp == NULL || temp[0] == NULL || temp[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_hitbox.hitbox = (sfFloatRect) {-atof(temp[0]) / 2.,
        -atof(temp[1]) / 2., atof(temp[0]), atof(temp[1])};
    if (entity->comp_hitbox.hitbox.width < 0 ||
        entity->comp_hitbox.hitbox.height < 0)
        return int_display_and_return(84, 3, "Invalid hitbox: ", args, "\n");
    return 0;
}
