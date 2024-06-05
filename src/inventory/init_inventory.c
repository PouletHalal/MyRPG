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

int init_select_cursor(world_t *world, entity_t *entity)
{
    comp_inventory_t *c_inv = &entity->comp_inventory;
    sfFloatRect bounds = {0};

    c_inv->cursor_sprite.sprite = sfSprite_create();
    c_inv->cursor_sprite.texture = sfTexture_createFromFile(
    "effect/inventory_select.png", NULL);
    sfSprite_setTexture(c_inv->cursor_sprite.sprite,
    c_inv->cursor_sprite.texture, sfTrue);
    bounds = sfSprite_getGlobalBounds(c_inv->cursor_sprite.sprite);
    sfSprite_setOrigin(c_inv->cursor_sprite.sprite,
    (sfVector2f) {bounds.width / 2, bounds.height / 2});
    sfSprite_setScale(c_inv->cursor_sprite.sprite,
    (sfVector2f) {3, 3});
    sfSprite_setPosition(c_inv->cursor_sprite.sprite, (sfVector2f){8, 74});
}

int init_inventory(world_t *world, entity_t *entity, int size)
{
    sfFloatRect bounds = {0};

    entity->mask |= COMP_INVENTORY;
    entity->comp_inventory.size = size;
    entity->comp_inventory.sprite.sprite = sfSprite_create();
    entity->comp_inventory.sprite.texture = sfTexture_createFromFile(
    "effect/inventory.png", NULL);
    init_select_cursor(world, entity);
    sfSprite_setTexture(entity->comp_inventory.sprite.sprite,
    entity->comp_inventory.sprite.texture, sfTrue);
    entity->comp_inventory.items = malloc(sizeof(entity_t) * size);
    entity->comp_inventory.base_rect = sfSprite_getTextureRect(
        entity->comp_inventory.sprite.sprite);
    entity->comp_inventory.scale = (sfVector2f){3, 3};
    bounds = sfSprite_getGlobalBounds(entity->comp_inventory.sprite.sprite);
    sfSprite_setOrigin(entity->comp_inventory.sprite.sprite,
    (sfVector2f) {bounds.width / 2, bounds.height / 2});
    sfSprite_setScale(entity->comp_inventory.sprite.sprite,
    (sfVector2f) {3, 3});
    init_items(entity);
}
