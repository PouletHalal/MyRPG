/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** npc_parsing
*/

#include <stdlib.h>
#include <string.h>
#include "temp.h"
#include "error_handling.h"
#include "dialogs.h"
#include "ecs.h"

int set_npc_pos(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    sfVector2f pos = {0};
    char **temp = NULL;
    int id = entity->comp_position.world;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(split[1], ",");
    if (temp == NULL || temp[0] == NULL || temp[1] == NULL)
        return 84;
    pos.x = atof(temp[0]);
    pos.y = atof(temp[1]);
    if (pos.x < 0 || pos.y < 0 || pos.x > world->map_list[id]->maps->size.x ||
        pos.y > world->map_list[id]->maps->size.y)
        return int_display_and_return(84, 3, "Invalid pos: ", split[1], "\n");
    init_comp_position(entity, pos, id);
}

int set_world_id(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    int nb_maps = 0;

    for (nb_maps = 0; world->map_list[nb_maps] != NULL; nb_maps++);
    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_position.world = atoi(split[1]);
    if (entity->comp_position.world < 0 ||
    entity->comp_position.world >= nb_maps)
        return int_display_and_return(84, 3, "Invalid world id: ",
        split[1], "\n");
    return 0;
}

int set_idle(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    int anim_index = 0;
    animation_t *anim = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    anim_index = get_anim_id(world, split[1]);
    if (anim_index == -1) {
        int_display_and_return(84, 3, "Invalid anim: ", split[1], "\n");
        anim_index = 0;
    }
    anim = &world->animations[anim_index];
    init_comp_render(entity, world, anim,
    entity->comp_position.position);
    init_comp_hitbox(entity, entity->comp_position.position);
    if (!strcmp(split[1], "intro") || !strcmp(split[1], "transparent"))
        entity->comp_hitbox.do_collide = sfFalse;
    return 0;
}

int set_color(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, "=\n ");
    char **temp = NULL;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(split[1], ", \n\t");
    if (temp == NULL || temp[0] == NULL || temp[1] == NULL || temp[2] == NULL)
        return 84;
    entity->comp_dialog.color.r = atoi(temp[0]);
    entity->comp_dialog.color.g = atoi(temp[1]);
    entity->comp_dialog.color.b = atoi(temp[2]);
    entity->comp_dialog.color.a = 255;
    if (entity->comp_dialog.color.a < 0 || entity->comp_dialog.color.a > 255 ||
        entity->comp_dialog.color.r < 0 || entity->comp_dialog.color.r > 255 ||
        entity->comp_dialog.color.g < 0 || entity->comp_dialog.color.g > 255 ||
        entity->comp_dialog.color.b < 0 || entity->comp_dialog.color.b > 255)
        return int_display_and_return(84, 3, "Invalid color:", split[1], "\n");
    return 0;
}

int set_box(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    sfTexture *texture = NULL;
    sfFloatRect bounds = {0};

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    entity->comp_dialog.box = sfSprite_create();
    texture = sfTexture_createFromFile(split[1], NULL);
    if (texture == NULL)
        return int_display_and_return(84, 3, "Invalid dialog box: ",
        split[1], "\n");
    sfSprite_setTexture(entity->comp_dialog.box, texture, true);
    return 0;
}
