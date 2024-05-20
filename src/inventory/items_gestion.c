/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** items_gestion
*/

#include "temp.h"

static bool is_mouse_over(sfVector2i pos, entity_t *entity)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(entity->comp_render.sprite);

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
        entity->comp_inventory.is_open == false)
        return false;
    items = entity->comp_inventory.items;
    item_pos = sfSprite_getPosition(
    world->entity[items[i].id_in_world].comp_render.sprite);
    if (is_mouse_over(mouse_pos, &world->entity[items[i].id_in_world])
        && !world->mouse_left_pressed) {
        display_tooltips(
        window, &world->entity[items[i].id_in_world], item_pos);
        return true;
    }
    return false;
}

static bool drop_item(win_t *window, entity_t *player, entity_t *item, int i)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);

    if (player->comp_input.mouse_left_down == false)
        return false;
    if (item->comp_item.type_mask == 0)
        return false;
    if (is_mouse_over(mouse_pos, item)) {
        item->comp_render.is_visible = true;
        sfSprite_setScale(item->comp_render.sprite, (sfVector2f) {0.5, 0.5});
        player->comp_inventory.items[i].type_mask = 0;
        item->comp_position.position = player->comp_position.position;
        sfSprite_setPosition(item->comp_render.sprite,
        player->comp_position.position);
        return true;
    }
    return false;
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
            is_close(&world->entity[i], entity, (sfVector2f) {16, 16})) {
            return add_item_to_inv(entity, &world->entity[i], i);
        }
    }
    return false;
}
