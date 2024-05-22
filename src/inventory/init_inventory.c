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

int init_inventory(world_t *world, entity_t *entity, int size)
{
    sfFloatRect bounds = {0};

    entity->mask |= COMP_INVENTORY;
    entity->comp_inventory.size = size;
    entity->comp_inventory.sprite.sprite = sfSprite_create();
    entity->comp_inventory.sprite.texture = sfTexture_createFromFile(
    "effect/inventory.png", NULL);
    sfSprite_setTexture(entity->comp_inventory.sprite.sprite,
    entity->comp_inventory.sprite.texture, sfTrue);
    entity->comp_inventory.items = malloc(sizeof(entity_t) * size);
    bounds = sfSprite_getGlobalBounds(entity->comp_inventory.sprite.sprite);
    sfSprite_setOrigin(entity->comp_inventory.sprite.sprite,
    (sfVector2f) {bounds.width / 2, bounds.height / 2});
    sfSprite_setScale(entity->comp_inventory.sprite.sprite,
    (sfVector2f) {3, 3});
    init_items(entity);
}
