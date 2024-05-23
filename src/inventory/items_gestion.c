/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** items_gestion
*/

#include <stdio.h>
#include <string.h>
#include "temp.h"

int get_item_id(item_list_t items, char const *name)
{
    for (int i = 0; i < items.nb_items; i++) {
        if (strcmp(items.items[i].tooltip.name, name) == 0) {
            return i;
        }
    }
    return 0;
}

static bool is_mouse_over(sfVector2i pos, entity_t *entity)
{
    sfFloatRect bounds = {0};

    if ((entity->mask & COMP_RENDER) != COMP_RENDER)
        return false;
    bounds = sfSprite_getGlobalBounds(entity->comp_render.sprite);
    if (pos.x >= bounds.left && pos.x <= bounds.left + bounds.width
        && pos.y >= bounds.top && pos.y <= bounds.top + bounds.height)
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
        entity->comp_inventory.is_open == false ||
        i >= entity->comp_inventory.size)
        return false;
    items = entity->comp_inventory.items;
    if (items[i].type_mask == 0)
        return false;
    item_pos = sfSprite_getPosition(
    world->entity[items[i].id_in_world].comp_render.sprite);
    if (is_mouse_over(mouse_pos, &world->entity[items[i].id_in_world])
        && !world->mouse_left_pressed && !world->mouse_right_pressed) {
        display_tooltips(
        window, &world->entity[items[i].id_in_world], item_pos);
        return true;
    }
    return false;
}

static bool drop_item(win_t *window, entity_t *player, entity_t *item, int i)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);

    if (player->comp_input.mouse_right_down == false)
        return false;
    if (item->comp_item.type_mask == 0 ||
        (item->comp_item.type_mask & ITEM_KEY) == ITEM_KEY)
        return false;
    if (is_mouse_over(mouse_pos, item)) {
        item->comp_render.is_visible = true;
        sfSprite_setScale(item->comp_render.sprite, (sfVector2f) {0.5, 0.5});
        player->comp_inventory.items[i].type_mask = 0;
        item->comp_position.position = player->comp_position.position;
        sfSprite_setPosition(item->comp_render.sprite,
        player->comp_position.position);
        item->comp_position.world = player->comp_position.world;
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
    item->comp_stat = (comp_stat_t) {0};
}

bool use_item(win_t *window, entity_t *player, entity_t *item, int i)
{
    if (!player->comp_input.mouse_left_down || !item->comp_item.type_mask ||
        !is_mouse_over(sfMouse_getPositionRenderWindow(window->window), item)
        || (item->comp_item.type_mask & ITEM_CONSUMABLE) != ITEM_CONSUMABLE)
        return false;
    update_stat(player, item);
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
        if (use_item(window, entity, &world->entity[entity->
        comp_inventory.items[i].id_in_world], i))
            return;
    }
}

bool item_collision(world_t *world, entity_t *entity)
{
    if (entity->comp_position.world != world->map_id ||
        (entity->mask & COMP_PLAYER) != COMP_PLAYER)
        return false;
    if (world->key_pressed[sfKeyF] == false)
        return false;
    for (int i = 0; i < ENTITY_COUNT; i++) {
        if ((world->entity[i].mask & COMP_ITEM) == COMP_ITEM &&
            world->entity[i].comp_render.is_visible &&
            is_close(&world->entity[i], entity, (sfVector2f) {10, 10})) {
                world->entity[i].comp_render.is_visible = false;
            return add_item_to_inv(entity, &world->entity[i], i);
        }
    }
    return false;
}
