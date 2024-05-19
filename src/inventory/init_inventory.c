/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_inventory
*/

#include <stdlib.h>
#include "temp.h"


static void init_items(entity_t *entity)
{
    for (int i = 0; i < entity->comp_inventory.size; i++) {
        entity->comp_inventory.items[i] = (comp_item_t) {0};
    }
}

/* void init_item(world_t *world, entity_t *entity, sfVector2f pos)
{
    sfVector2u item_size = {0};
    int free_slot = find_empty(world);
    entity_t *item = &world->entity[free_slot];

    init_comp_position(item, pos, world->map_id);
    init_comp_render(item, world, ANIM_ITEM, pos);
    item->mask |= COMP_ITEM;
    item->comp_item.type_mask |= ITEM_EQUIPABLE;
    item->comp_item.equip_mask = CHESTPLATE;
    item->comp_item.id = 1;
    item->comp_item.quantity = 1;
} */

int init_inventory(world_t *world, entity_t *entity, int size)
{
    sfVector2u sprite_size = {0};

    entity->mask |= COMP_INVENTORY;
    entity->comp_inventory.size = size;
    entity->comp_inventory.sprite.sprite = sfSprite_create();
    entity->comp_inventory.sprite.texture = sfTexture_createFromFile(
        "effect/inventory.png", NULL);
    sfSprite_setTexture(entity->comp_inventory.sprite.sprite,
    entity->comp_inventory.sprite.texture, sfTrue);
    entity->comp_inventory.items = malloc(sizeof(entity_t) * size);
    sprite_size = sfTexture_getSize(entity->comp_inventory.sprite.texture);
    sfSprite_setOrigin(entity->comp_inventory.sprite.sprite,
    (sfVector2f){sprite_size.x / 2, sprite_size.y / 2});
    init_items(entity);
}
