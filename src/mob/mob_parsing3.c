/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** mob_parsing
*/

#include <stdlib.h>
#include <string.h>
#include "error_handling.h"
#include "mob.h"
#include "ecs.h"

int set_does_rand(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_mob.does_rand_spawn = GET_BOOL(split[1]);
    if (entity->comp_mob.does_rand_spawn) {
        entity->comp_mob.is_alive = false;
        entity->comp_render.is_visible = false;
    }
    free_array(split);
    return 0;
}

int set_spawn_rate(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atof(split[1]) < 0.) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_mob.spawn_rate = atof(split[1]);
    free_array(split);
    return 0;
}

int set_mob_pos(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    sfVector2f pos = {0};
    char **temp = NULL;
    int id = entity->comp_position.world;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    temp = my_str_to_word_array(split[1], ",");
    if (temp == NULL || temp[0] == NULL || temp[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    pos.x = atof(temp[0]);
    pos.y = atof(temp[1]);
    if (pos.x < 0 || pos.y < 0 || pos.x > world->map_list[id]->maps->size.x ||
        pos.y > world->map_list[id]->maps->size.y)
        return int_display_and_return(84, 3, "Invalid pos: ", split[1], "\n");
    init_comp_position(entity, pos, id);
    free(temp);
    return 0;
}

int set_anim(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");
    int anim_index = 0;

    if (split == NULL || split[1] == NULL)
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    anim_index = get_anim_id(world, split[1]);
    if (anim_index == -1) {
        int_display_and_return(84, 3, "Invalid anim: ", split[1], "\n");
        anim_index = 0;
    }
    entity->comp_mob.anim_id = anim_index;
    init_comp_render(entity, world, &world->animations[anim_index],
    entity->comp_position.position);
    init_comp_hitbox(entity, entity->comp_position.position);
    if (!strcmp(split[1], "intro") || !strcmp(split[1], "transparent"))
        entity->comp_hitbox.do_collide = sfFalse;
    return 0;
}
