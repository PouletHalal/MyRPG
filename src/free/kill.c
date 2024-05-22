/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** kill
*/

#include "temp.h"

void kill_entity(entity_t *entity, world_t *world)
{
    if ((entity->mask & COMP_MOB == COMP_MOB) && entity->comp_mob.is_clone)
            world->entity[entity->comp_mob.clone].comp_mob.mob_count -= 1;
    if ((entity->mask & COMP_RENDER) == COMP_RENDER) {
        sfTexture_destroy(entity->comp_render.texture);
        sfSprite_destroy(entity->comp_render.sprite);
    }
    entity->mask = COMP_NONE;
}
