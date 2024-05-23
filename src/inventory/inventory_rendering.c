/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** inventory_rendering
*/

#include "temp.h"
#include "player.h"
#include "inventory.h"

static void place_item(world_t *world, entity_t *entity, int i)
{
    sfVector2f item_pos = get_pos_from_slot(entity, i);

    if (!entity->comp_inventory.is_open)
        return;
    world->entity[entity->comp_inventory.items[i].id_in_world].
    comp_position.position = item_pos;
    world->entity[entity->comp_inventory.items[i].id_in_world].
    comp_position.can_move = false;
    sfSprite_setPosition(world->entity[entity->comp_inventory.
    items[i].id_in_world].comp_render.sprite,
    item_pos);
    sfSprite_setScale(world->entity[entity->comp_inventory.items[i].
    id_in_world].comp_render.sprite,
    (sfVector2f) {2, 2});
}

static void display_items(win_t *window, world_t *world, entity_t *entity)
{
    sfVector2u inv_size = sfTexture_getSize(entity->comp_inventory.sprite.
    texture);
    sfVector2f inv_pos = sfSprite_getPosition(entity->comp_inventory.sprite.
    sprite);

    for (int i = 0; i < entity->comp_inventory.size; i++) {
        if (entity->comp_inventory.items[i].type_mask != 0
        && !entity->comp_inventory.items[i].is_picked)
            place_item(world, entity, i);
        if (entity->comp_inventory.items[i].type_mask != 0
        && world->entity[entity->comp_inventory.items[i].id_in_world]
        .comp_inventory.is_visible) {
            sfRenderWindow_drawSprite(window->window, world->entity[
                entity->comp_inventory.items[i].id_in_world]
                .comp_render.sprite, NULL);
        }
    }
}

static void turn_off_items(world_t *world, entity_t *entity, win_t *window,
    sfVector2u win_size)
{
    sfRenderWindow_setView(window->window,
    sfRenderWindow_getDefaultView(window->window));
    sfSprite_setPosition(entity->comp_inventory.sprite.sprite,
    (sfVector2f) {win_size.x / 2, win_size.y / 2 + 500});
    sfSprite_setTextureRect(entity->comp_inventory.sprite.sprite,
    (sfIntRect){0, 67, 203, 30});
    for (int i = 0; i < entity->comp_inventory.size; i++) {
        if (entity->comp_inventory.items[i].type_mask != 0 && i > 17) {
            world->entity[entity->comp_inventory.items[i].id_in_world].
            comp_position.position = (sfVector2f){world->entity[entity->
            comp_inventory.items[i].id_in_world].comp_position.position.x,
            win_size.y / 2 + 402};
        }
        if (entity->comp_inventory.items[i].type_mask != 0 && i <= 17) {
            world->entity[entity->comp_inventory.items[i].id_in_world]
            .comp_inventory.is_visible = false;
        }
    }
    sfRenderWindow_drawSprite(window->window, entity->comp_inventory.sprite.sprite, NULL);
    display_items(window, world, entity);
}

void display_inventory(win_t *window, world_t *world)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];
    sfVector2u win_size = sfRenderWindow_getSize(window->window);

    if (!player->comp_inventory.is_open)
        return turn_off_items(world, player, window, win_size);
    for (int i = 0; i < player->comp_inventory.size; i++)
        world->entity[player->comp_inventory.items[i].id_in_world].comp_inventory.is_visible = true;
    sfRenderWindow_setView(window->window,
    sfRenderWindow_getDefaultView(window->window));
    sfSprite_setTextureRect(player->comp_inventory.sprite.sprite, player->comp_inventory.base_rect);
    sfSprite_setPosition(player->comp_inventory.sprite.sprite,
    (sfVector2f) {win_size.x / 2, win_size.y / 2});
    sfRenderWindow_drawSprite(window->window,
    player->comp_inventory.sprite.sprite, NULL);
    player->comp_inventory.sprite.pos = (sfVector2f) {win_size.x / 2,
    win_size.y / 2};
    display_items(window, world, player);
    manage_inv_slots(world, window, player);
    item_events(window, world, player);
}
