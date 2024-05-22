/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** inventory_gestion
*/

#include "world.h"

sfBool is_in_inv(world_t *world, entity_t *entity, int id)
{
    if ((entity->mask & COMP_INVENTORY) != COMP_INVENTORY)
        return sfFalse;
    for (int i = 0; i < entity->comp_inventory.size; ++i) {
        if (entity->comp_inventory.items[i].type_mask != 0
            && entity->comp_inventory.items[i].id == id) {
            return sfTrue;
        }
    }
    return sfFalse;
}

int find_empty_slot(entity_t *entity)
{
    for (int i = 0; i < entity->comp_inventory.size; i++) {
        if (entity->comp_inventory.items[i].type_mask == COMP_NONE) {
            return i;
        }
    }
    return -1;
}

bool add_item_to_inv(entity_t *entity, entity_t *item, int i)
{
    int slot = find_empty_slot(entity);

    if (slot == -1)
        return false;
    if ((entity->mask & COMP_INVENTORY) != COMP_INVENTORY)
        return false;
    for (int i = 0; i < entity->comp_inventory.size; ++i) {
        if (((entity->comp_inventory.items[i].type_mask != 0) &&
            entity->comp_inventory.items[i].id_in_world == item->comp_item.id_in_world)) {
            return false;
        }
    }
    item->comp_item.id_in_world = i;
    item->comp_render.is_visible = false;
    entity->comp_inventory.items[slot] = item->comp_item;
    return true;
}
