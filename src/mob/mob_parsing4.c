/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** mob_parsing4
*/

#include <stdlib.h>
#include <string.h>
#include "error_handling.h"
#include "mob.h"
#include "temp.h"
#include "ecs.h"

int set_exp_loot(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n");

    if (split == NULL || split[1] == NULL || atof(split[1]) < 0.) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    entity->comp_stat.exp_loot = atof(split[1]);
    free_array(split);
    return 0;
}

int set_healthbar(world_t *world, entity_t *entity, char *args)
{
    char **split = my_str_to_word_array(args, " =\n\t");
    entity_t *healthbar = NULL;
    int id = find_empty(world);

    if (split == NULL || split[1] == NULL) {
        free_array(split);
        return int_display_and_return(84, 3, "Invalid args: ", args, "\n");
    }
    if (id < 0)
        return int_display_and_return(84, 1, "No more space for healthbars\n");
    healthbar = &world->entity[id];
    init_comp_render(healthbar, world, &world->animations[get_anim_id(world,
    "healthbar")], (sfVector2f){0, 0});
    init_comp_position(healthbar, (sfVector2f)
    {entity->comp_position.position.x, entity->comp_position.position.y -
    entity->comp_render.current_animation->frame_size.y / 2},
    entity->comp_position.world);
    return 0;
}
