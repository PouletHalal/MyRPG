/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** items_gestion
*/

#include <stdio.h>
#include "temp.h"

sfVector2i inv_coords[18] = {
    {84, 8}, {103, 8}, {122, 8}, {141, 8}, {160, 8}, {179, 8},
    {84, 27}, {103, 27}, {122, 27}, {141, 27}, {160, 27}, {179, 27},
    {84, 46}, {103, 46}, {122, 46}, {141, 46}, {160, 46}, {179, 46}
};

static bool is_mouse_over(sfVector2i pos, entity_t *entity)
{
    sfFloatRect bounds = {0};

    if ((entity->mask & COMP_RENDER) != COMP_RENDER)
        return false;
    bounds = sfSprite_getGlobalBounds(entity->comp_render.sprite);
    if (pos.x >= bounds.left && pos.x <= bounds.left + bounds.width &&
    pos.y >= bounds.top && pos.y <= bounds.top + bounds.height)
        return true;
    return false;
}

static bool item_higlighting(win_t *window, world_t *world,
    entity_t *entity, int i)
{
    comp_item_t *items = NULL;
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);
    sfVector2f item_pos = {0};

    if ((entity->mask & COMP_INVENTORY) != COMP_INVENTORY ||
        entity->comp_inventory.is_open == false)
        return false;
    items = entity->comp_inventory.items;
    if (items[i].type_mask == 0)
        return false;
    item_pos = sfSprite_getPosition(
        world->entity[items[i].id_in_world].comp_render.sprite);
    if (is_mouse_over(mouse_pos, &world->entity[items[i].id_in_world]) &&
    !world->mouse_left_pressed && !world->mouse_right_pressed) {
        display_tooltips(
            window, &world->entity[items[i].id_in_world], item_pos);
        return true;
    }
    return false;
}

static bool drop_item(win_t *window, entity_t *player, entity_t *item, int i)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);

    //if (player->comp_input.mouse_right_down == false)
    //    return false;
    if (item->comp_item.type_mask == 0)
        return false;
    if (is_mouse_over(mouse_pos, item)) {
        item->comp_render.is_visible = true;
        sfSprite_setScale(item->comp_render.sprite, (sfVector2f){0.5, 0.5});
        player->comp_inventory.items[i].type_mask = 0;
        item->comp_position.position = player->comp_position.position;
        sfSprite_setPosition(item->comp_render.sprite,
        player->comp_position.position);
        return true;
    }
    return false;
}

static void update_stat(entity_t *player, entity_t *item)
{
    player->comp_stat.health += item->comp_stat.health;
    if (player->comp_stat.health > player->comp_stat.max_health)
        player->comp_stat.health = player->comp_stat.max_health;
    player->comp_stat.damage += item->comp_stat.damage;
    if (player->comp_stat.damage < 0)
        player->comp_stat.damage = 0;
    player->comp_stat.defense += item->comp_stat.defense;
    if (player->comp_stat.defense < 0)
        player->comp_stat.defense = 0;
    item->comp_stat = (comp_stat_t){0};
}

bool use_item(win_t *window, entity_t *player, entity_t *item, int i)
{
    if (!player->comp_input.mouse_left_down || !item->comp_item.type_mask ||
        !is_mouse_over(sfMouse_getPositionRenderWindow(window->window), item)
        || (item->comp_item.type_mask & ITEM_CONSUMABLE) != ITEM_CONSUMABLE)
        return false;
    // printf("player health BEFORE = %f\n", player->comp_stat.health);
    // printf("player defense BEFORE = %f\n", player->comp_stat.defense);
    // printf("player attack BEFORE = %f\n", player->comp_stat.damage);
    update_stat(player, item);
    // printf("player health AFTER = %f\n", player->comp_stat.health);
    // printf("player defense AFTER = %f\n", player->comp_stat.defense);
    // printf("player attack AFTER = %f\n", player->comp_stat.damage);
    player->comp_inventory.items[i].type_mask = 0;
    item->comp_render.is_visible = false;
    return true;
}

void item_events(win_t *window, world_t *world, entity_t *entity)
{
    if ((entity->mask & COMP_INVENTORY) != COMP_INVENTORY ||
        entity->comp_inventory.is_open == false)
        return;
    for (int i = 0; i < entity->comp_inventory.size; i++) {
        if (item_higlighting(window, world, entity, i))
            return;
        if (drop_item(window, entity, &world->entity[entity->
        comp_inventory.items[i].id_in_world], i))
            return;
        // if (use_item(window, entity, &world->entity[entity->
        // comp_inventory.items[i].id_in_world], i))
        //     return;
    }
}

bool item_collision(world_t *world, entity_t *entity)
{
    if (entity->comp_position.world != world->map_id ||
        (entity->mask & COMP_PLAYER) != COMP_PLAYER)
        return false;
    if (world->key_pressed[sfKeyE] == false)
        return false;
    for (int i = 0; i < ENTITY_COUNT; i++) {
        if ((world->entity[i].mask & COMP_ITEM) == COMP_ITEM &&
            world->entity[i].comp_render.is_visible &&
            is_close(&world->entity[i], entity, (sfVector2f){16, 16})) {
            return add_item_to_inv(entity, &world->entity[i], i);
        }
    }
    return false;
}

int get_slot_from_mouse_pos(win_t *window, entity_t *entity)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);
    sfVector2i bounds = (sfVector2i){sfSprite_getGlobalBounds(
        entity->comp_inventory.sprite.sprite).width,
        sfSprite_getGlobalBounds(entity->comp_inventory.sprite.sprite).height};
    sfVector2i inv_pos = (sfVector2i){sfSprite_getPosition(
        entity->comp_inventory.sprite.sprite).x - (bounds.x / 2),
        sfSprite_getPosition(entity->comp_inventory.sprite.sprite).y
        - (bounds.y / 2)};
    int slot_size = 19 * 3;

    for (int i = 0; i < 18; i++) {
        if ((mouse_pos.x >= (inv_coords[i].x * 3+ inv_pos.x)
        && mouse_pos.x <= (inv_coords[i].x * 3+ inv_pos.x + slot_size))
        && (mouse_pos.y >= (inv_coords[i].y * 3+ inv_pos.y)
        && mouse_pos.y <= (inv_coords[i].y * 3 + inv_pos.y + slot_size)))
                return i;
    }
    return -1;
}

void manage_inv_slots(world_t *world, win_t *window, entity_t *entity)
{
    int mouse_id = find_comp(world, COMP_MOUSE);
    entity_t *mouse = &world->entity[mouse_id];
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);
    comp_item_t *items = entity->comp_inventory.items;
    comp_item_t temp = (comp_item_t) {0};
    int slot = get_slot_from_mouse_pos(window, entity);

    if (mouse->comp_mouse.item_picked) {
        world->entity[items[mouse->comp_mouse.item_picked_i].id_in_world].comp_position.position = (sfVector2f){mouse_pos.x, mouse_pos.y};
        if (world->mouse_left_pressed) {
            world->mouse_left_pressed = false;
            if (slot > 0) {
            entity->comp_inventory.items[mouse->comp_mouse.item_picked_i].is_picked = false;
            temp = entity->comp_inventory.items[mouse->comp_mouse.item_picked_i];
            entity->comp_inventory.items[mouse->comp_mouse.item_picked_i] = entity->comp_inventory.items[slot];
            entity->comp_inventory.items[slot] = temp;

            mouse->comp_mouse.item_picked = false;
            mouse->comp_mouse.item_picked_i = 0;
            } else {
                mouse->comp_mouse.item_picked = false;
                drop_item(window, entity, &world->entity[items[mouse->comp_mouse.item_picked_i].id_in_world], mouse->comp_mouse.item_picked_i);
                mouse->comp_mouse.item_picked_i = 0;
            }
        }
        return;
    }
    for (int i = 0; i < entity->comp_inventory.size; i++)
    {
        if (entity->comp_inventory.items[i].type_mask != 0)
        {
            if (is_mouse_over(mouse_pos, &world->entity[items[i].id_in_world]) && world->mouse_left_pressed)
            {
                mouse->comp_mouse.item_picked = true;
                mouse->comp_mouse.item_picked_i = i;
                entity->comp_inventory.items[i].is_picked = true;
                world->mouse_left_pressed = false;
                world->entity[items[i].id_in_world].comp_position.position = (sfVector2f){mouse_pos.x, mouse_pos.y};
                return;
            }
        }
    }
}
