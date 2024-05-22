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
        if (entity->comp_inventory.items[i].type_mask != 0) {
            if (!entity->comp_inventory.items[i].is_picked)
                place_item(world, entity, i);
            sfRenderWindow_drawSprite(window->window,
            world->entity[entity->comp_inventory.items[i].id_in_world].
            comp_render.sprite, NULL);
        }
    }
}

static void turn_off_items(world_t *world, entity_t *entity)
{
    for (int i = 0; i < entity->comp_inventory.size; i++) {
        if (entity->comp_inventory.items[i].type_mask != 0) {
            world->entity[entity->comp_inventory.items[i].id_in_world].
            comp_render.is_visible = false;
        }
    }
}

void display_inventory(win_t *window, world_t *world)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];
    sfVector2u win_size = sfRenderWindow_getSize(window->window);

    if (player->comp_inventory.is_open == false)
        return turn_off_items(world, player);
    sfRenderWindow_setView(window->window,
    sfRenderWindow_getDefaultView(window->window));
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
