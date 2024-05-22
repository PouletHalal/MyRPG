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

sfVector2f get_pos_from_slot(entity_t *entity, int slot)
{
    sfVector2i bounds = (sfVector2i){sfSprite_getGlobalBounds(
        entity->comp_inventory.sprite.sprite).width,
        sfSprite_getGlobalBounds(entity->comp_inventory.sprite.sprite).height};
    sfVector2i inv_pos = (sfVector2i){sfSprite_getPosition(
        entity->comp_inventory.sprite.sprite).x - (bounds.x / 2),
        sfSprite_getPosition(entity->comp_inventory.sprite.sprite).y
        - (bounds.y / 2)};
    int slot_size = 19 * 3;
    sfVector2f pos = (sfVector2f){0};

    pos = (sfVector2f){inv_coords[slot].x * 3 + inv_pos.x + slot_size / 2,
    inv_coords[slot].y * 3 + inv_pos.y + slot_size / 2};
    return pos;
}

int get_slot_from_pos(entity_t *entity, sfVector2i mouse_pos)
{
    sfVector2i bounds = (sfVector2i){sfSprite_getGlobalBounds(
        entity->comp_inventory.sprite.sprite).width,
        sfSprite_getGlobalBounds(entity->comp_inventory.sprite.sprite).height};
    sfVector2i inv_pos = (sfVector2i){sfSprite_getPosition(
        entity->comp_inventory.sprite.sprite).x - (bounds.x / 2),
        sfSprite_getPosition(entity->comp_inventory.sprite.sprite).y
        - (bounds.y / 2)};
    int slot_size = 19 * 3;

    for (int i = 0; i < 28; i++) {
        if ((mouse_pos.x >= (inv_coords[i].x * 3+ inv_pos.x)
        && mouse_pos.x <= (inv_coords[i].x * 3+ inv_pos.x + slot_size))
        && (mouse_pos.y >= (inv_coords[i].y * 3+ inv_pos.y)
        && mouse_pos.y <= (inv_coords[i].y * 3 + inv_pos.y + slot_size)))
                return i;
    }
    if (mouse_pos.x >= inv_pos.x && mouse_pos.y >= inv_pos.y &&
    mouse_pos.x <= inv_pos.x + bounds.x && mouse_pos.y <= inv_pos.y + bounds.y)
        return -2;
    return -1;
}

static void pick_item(world_t *world, entity_t *entity,
    sfVector2i mouse_pos, entity_t *mouse)
{
    comp_item_t *items = entity->comp_inventory.items;

    for (int i = 0; i < entity->comp_inventory.size; i++) {
        if ((entity->comp_inventory.items[i].type_mask != 0)
        && (is_mouse_over(mouse_pos, &world->entity[items[i].id_in_world])
        && world->mouse_left_pressed)) {
            mouse->comp_mouse.item_picked = true;
            mouse->comp_mouse.item_picked_i = i;
            entity->comp_inventory.items[i].is_picked = true;
            world->mouse_left_pressed = false;
            world->entity[items[i].id_in_world].comp_position.position =
            (sfVector2f){mouse_pos.x, mouse_pos.y};
            return;
        }
    }
}

static void drag_item_inv(entity_t *entity, entity_t *mouse, int slot)
{
    comp_item_t temp = (comp_item_t) {0};

    entity->comp_inventory.items[
        mouse->comp_mouse.item_picked_i].is_picked = false;
    temp = entity->comp_inventory.items[mouse->comp_mouse.item_picked_i];
    entity->comp_inventory.items[mouse->comp_mouse.item_picked_i] =
    entity->comp_inventory.items[slot];
    entity->comp_inventory.items[slot] = temp;
    mouse->comp_mouse.item_picked = false;
    mouse->comp_mouse.item_picked_i = 0;
}

static void drop_item_inv(entity_t *entity, world_t *world,
    sfVector2i mouse_pos, entity_t *mouse)
{
    comp_item_t *items = entity->comp_inventory.items;

    mouse->comp_mouse.item_picked = false;
    drop_item(entity, &world->entity[items[
        mouse->comp_mouse.item_picked_i].id_in_world], mouse_pos,
        mouse->comp_mouse.item_picked_i);
    mouse->comp_mouse.item_picked_i = -1;
}

void manage_picked_item(world_t *world, entity_t *entity,
    sfVector2i mouse_pos, entity_t *mouse)
{
    int slot = get_slot_from_pos(entity, mouse_pos);

    if (world->key_pressed[sfKeyA]) {
        drop_item_inv(entity, world, mouse_pos, mouse);
        return;
    }
    if (world->mouse_left_pressed) {
        world->mouse_left_pressed = false;
        if (slot >= 0)
            drag_item_inv(entity, mouse, slot);
        if (slot == -1)
            drop_item_inv(entity, world, mouse_pos, mouse);
    }
    return;
}

void manage_inv_slots(world_t *world, win_t *window, entity_t *entity)
{
    int mouse_id = find_comp(world, COMP_MOUSE);
    entity_t *mouse = &world->entity[mouse_id];
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);
    comp_item_t *items = entity->comp_inventory.items;

    if (mouse->comp_mouse.item_picked) {
        world->entity[items[mouse->comp_mouse.item_picked_i].id_in_world]
        .comp_position.position = (sfVector2f){mouse_pos.x, mouse_pos.y};
        manage_picked_item(world, entity, mouse_pos, mouse);
        return;
    }
    pick_item(world, entity, mouse_pos, mouse);
}
