/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my_rpg
*/

#include "temp.h"
#include "player.h"
#include "inventory.h"
#include "world.h"

int get_slot_in_hotbar(entity_t *entity, sfVector2i mouse_pos)
{
    sfVector2i bounds = (sfVector2i){sfSprite_getGlobalBounds(
        entity->comp_inventory.sprite.sprite).width,
        sfSprite_getGlobalBounds(entity->comp_inventory.sprite.sprite).height};
    sfVector2i inv_pos = (sfVector2i){sfSprite_getPosition(
        entity->comp_inventory.sprite.sprite).x - (bounds.x / 2),
        sfSprite_getPosition(entity->comp_inventory.sprite.sprite).y
        - (bounds.y / 2)};
    int slot_size = 19 * 3;

    for (int i = 0; i < 10; i++) {
        if ((mouse_pos.x >= (hotbar_coords[i].x - slot_size / 2)
        && mouse_pos.x <= (hotbar_coords[i].x + slot_size / 2))
        && (mouse_pos.y >= (hotbar_coords[i].y - slot_size / 2)
        && mouse_pos.y <= (hotbar_coords[i].y + slot_size / 2)))
                return i;
    }
    if (mouse_pos.x >= inv_pos.x && mouse_pos.y >= inv_pos.y &&
    mouse_pos.x <= inv_pos.x + bounds.x && mouse_pos.y <= inv_pos.y + bounds.y)
        return -2;
    return -1;
}

int get_spell_selected(entity_t *entity)
{
    int slot = entity->comp_inventory.cursor_slot;
    int spell_id = entity->comp_inventory.items[slot + 18].spell_id;

    return spell_id;
}
