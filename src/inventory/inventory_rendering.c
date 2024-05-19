/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** inventory_rendering
*/

#include "temp.h"
#include "player.h"

static void display_items(win_t *window, world_t *world, entity_t *entity)
{
    sfVector2f item_pos = {0};
    sfVector2u inv_size = sfTexture_getSize(entity->comp_inventory.sprite.texture);
    sfVector2f inv_pos = sfSprite_getPosition(entity->comp_inventory.sprite.sprite);
    sfVector2f start =
    {
        inv_pos.x + 92 - inv_size.x / 2,
        inv_pos.y + 16 - inv_size.y / 2
    };

    for (int i = 0; i < entity->comp_inventory.size; i++) {
        if (entity->comp_inventory.items[i].type_mask != 0) {
            item_pos.x = start.x + (i % 6) * (16 + 3);
            item_pos.y = start.y + (i / 6) * (16 + 3);
            world->entity[entity->comp_inventory.items[i].id_in_world].comp_position.position = item_pos;
            world->entity[entity->comp_inventory.items[i].id_in_world].comp_render.is_visible = true;
            world->entity[entity->comp_inventory.items[i].id_in_world].comp_position.can_move = false;
            sfRenderWindow_drawSprite(window->window,
            world->entity[entity->comp_inventory.items[i].id_in_world].comp_render.sprite, NULL);
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

    if (player->comp_inventory.is_open == false)
        return turn_off_items(world, player);
    sfSprite_setPosition(player->comp_inventory.sprite.sprite,
    player->comp_position.position);
    sfRenderWindow_drawSprite(window->window,
    player->comp_inventory.sprite.sprite, NULL);
    player->comp_inventory.sprite.pos = player->comp_position.position;
    display_items(window, world, player);
}

