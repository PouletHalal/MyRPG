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

void npc_collision(win_t *window, world_t *world, entity_t *entity)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    if ((entity->mask & COMP_PLAYER) != COMP_PLAYER)
        return;
    for (size_t i = 0; i < ENTITY_COUNT; ++i) {
        if (world->entity[i].comp_position.world == world->map_id &&
            ((world->entity[i].mask & COMP_DIALOG) == COMP_DIALOG) &&
            ((is_close(entity, &world->entity[i], (sfVector2f) {30, 30}) ||
            world->entity[i].comp_dialog.is_displayed == true)) &&
            world->entity[i].comp_dialog.is_finished == false) {
            world->entity[i].comp_dialog.is_displayed = true;
            world->entity[i].comp_position.can_move = false;
            update_dialog(window, world, &world->entity[i]);
        }
    }
}
