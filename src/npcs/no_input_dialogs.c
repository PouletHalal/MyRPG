/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** no_input_dialogs
*/

#include "temp.h"
#include "dialogs.h"
#include "rendering.h"
#include "player.h"
#include "camera.h"

static void update_no_input_dialog(win_t *window, world_t *world,
    entity_t *entity, entity_t *player)
{
    comp_dialog_t *dialog = &entity->comp_dialog;

    player->comp_inventory.is_open = false;
    dialog->is_displayed = true;
    dialog->need_input = true;
    dialog->current_dialog = 0;
    dialog->current_sentence = 0;
    dialog->current_char = 0;
    if (dialog->camera_focus == true)
        set_destination(window, &entity->comp_position.position);
}

void no_input_dialogs(win_t *window, world_t *world)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];
    comp_dialog_t *dialog = NULL;

    for (int i = 0; i < ENTITY_COUNT; ++i) {
        dialog = &world->entity[i].comp_dialog;
        if (world->entity[i].comp_position.world == world->map_id
            && (world->entity[i].mask & COMP_DIALOG) == COMP_DIALOG &&
            is_close(player, &world->entity[i], dialog->detection_area) &&
            dialog->need_input == false && dialog->is_displayed != true) {
                dialog->need_input = true;
            play_animation(world, player, get_anim_id(world, "prota_idle"), 1);
            update_no_input_dialog(window, world, &world->entity[i], player);
                player->comp_position.can_move = !dialog->freeze_player;
        }
    }
}
