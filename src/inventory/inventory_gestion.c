/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** inventory_gestion
*/

#include "ecs.h"

int find_empty_slot(entity_t *entity)
{
    for (int i = 0; i < entity->comp_inventory.size; i++) {
        if (entity->comp_inventory.items[i].type_mask == COMP_NONE)
            return i;
    }
    return -1;
}

void add_item_to_inv(entity_t *entity, comp_item_t *item)
{
    int slot = find_empty_slot(entity);

    if (slot == -1)
        return;
    printf("added item in slot %d\n", slot);
    printf("item id in world = %d\n", item->id_in_world);
    entity->comp_inventory.items[slot] = *item;
}
