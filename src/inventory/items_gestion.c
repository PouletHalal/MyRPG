/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** items_gestion
*/

#include "temp.h"

bool item_collision(world_t *world, entity_t *entity)
{
    if (entity->comp_position.world != world->map_id ||
        (entity->mask & COMP_PLAYER) != COMP_PLAYER)
        return false;
    for (int i = 0; i < ENTITY_COUNT; i++) {
        if ((world->entity[i].mask & COMP_ITEM) == COMP_ITEM &&
            world->entity[i].comp_render.is_visible &&
            is_close(&world->entity[i], entity, (sfVector2f) {16, 16})) {
            world->entity[i].comp_render.is_visible = false;
            world->entity[i].comp_item.id_in_world = i;
            add_item_to_inv(entity, &world->entity[i].comp_item);
            return true;
        }
    }
    return false;
}
