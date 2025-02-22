/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** npc_gestion
*/

#include "temp.h"
#include "player.h"
#include "npcs.h"
#include "dialogs.h"

static void take_item(entity_t *player, entity_t *npc)
{
    for (int i = 0; i < player->comp_inventory.size; ++i) {
        if (player->comp_inventory.items[i].id ==
            npc->comp_npc.key_item_to_talk_id)
            player->comp_inventory.items[i].type_mask = 0;
    }
    return;
}

static bool need_item(world_t *world, entity_t *npc, entity_t *player)
{
    if (npc->comp_npc.need_key_item_to_talk == false)
        return true;
    if (is_in_inv(world, player, npc->comp_npc.key_item_to_talk_id)) {
        npc->comp_npc.need_key_item_to_talk = false;
        take_item(player, npc);
        return true;
    }
    return false;
}

void npc_events(win_t *window, world_t *world, entity_t *npc, entity_t *player)
{
    if (npc->comp_position.world == world->map_id &&
        ((npc->mask & COMP_DIALOG) == COMP_DIALOG)) {
        if (((is_close(player, npc, (sfVector2f) {32, 32}) ||
            npc->comp_dialog.is_displayed == true)) &&
            npc->comp_dialog.is_finished == false &&
            need_item(world, npc, player)) {
                npc->comp_dialog.is_displayed = true;
                return update_dialog(window, world, npc);
        }
    }
}

void npc_collision(win_t *window, world_t *world, entity_t *entity)
{
    if ((entity->mask & COMP_PLAYER) != COMP_PLAYER)
        return;
    if (world->ui_id != 0)
        return;
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        npc_events(window, world, &world->entity[i], entity);
    world->key_pressed[sfKeySpace] = false;
    world->key_down[sfKeySpace] = false;
}
