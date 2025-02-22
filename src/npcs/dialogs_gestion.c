/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** dialogs
*/

#include <stdlib.h>
#include <string.h>
#include "temp.h"
#include "maps.h"
#include "player.h"
#include "rendering.h"
#include "camera.h"
#include "dialogs.h"

static char *get_substring(char *str, int start, int end)
{
    char *new_str = malloc(sizeof(char) * (end - start + 1));
    int j = 0;

    for (int i = start; i < end; i++) {
        new_str[j] = str[i];
        j++;
    }
    new_str[j] = '\0';
    return new_str;
}

void update_substring(entity_t *entity, int dialog, int sentence)
{
    if (dialog == -1 || sentence == -1)
        return;
    if (entity->comp_dialog.text[dialog] == NULL)
        return;
    if (sfClock_getElapsedTime(entity->comp_dialog.clock).microseconds
        > 1e5 / 2 && entity->comp_dialog.current_char <
        strlen(entity->comp_dialog.text[dialog][sentence])) {
        entity->comp_dialog.current_char += 1;
        entity->comp_dialog.substring =
        get_substring(entity->comp_dialog.text[dialog][sentence], 0,
        entity->comp_dialog.current_char);
        sfClock_restart(entity->comp_dialog.clock);
    }
}

static bool is_last_sentence(entity_t *entity, entity_t *player,
    win_t *window, world_t *world)
{
    int dialog = entity->comp_dialog.current_dialog;
    int sentence = entity->comp_dialog.current_sentence;

    if (sentence + 1 >= len_array(entity->comp_dialog.text[dialog])) {
        entity->comp_dialog.current_sentence = -1;
        entity->comp_dialog.current_dialog += 1;
        entity->comp_dialog.is_displayed = false;
        player->comp_position.can_move = true;
        if (entity->comp_dialog.camera_focus == true)
            set_destination(window, &player->comp_position.position);
        if (entity->comp_npc.need_key_item_to_talk &&
            entity->comp_npc.takes_item)
            player->comp_inventory.items[find_item_in_inv(player,
            entity->comp_npc.key_item_to_talk_id)].type_mask = 0;
        return true;
    }
    return false;
}

static void mini_update_dialog(win_t *window, world_t *world, entity_t *entity)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    if (is_last_sentence(entity, player, window, world) == false) {
        entity->comp_dialog.current_char = 0;
        entity->comp_dialog.current_sentence += 1;
    }
    if (entity->comp_dialog.current_dialog >= entity->comp_dialog.nb_dialogs) {
        if (entity->comp_dialog.does_loop == false)
            entity->comp_dialog.is_finished = true;
        if (entity->comp_dialog.camera_focus == true)
            set_destination(window, &player->comp_position.position);
        entity->comp_dialog.is_displayed = false;
        player->comp_position.can_move = true;
        entity->comp_dialog.current_dialog = -1;
        entity->comp_dialog.current_sentence = 0;
        entity->comp_dialog.current_char = 0;
    }
}

static void delete_mark(world_t *world, entity_t *npc)
{
    int id = 0;

    if (!npc->comp_npc.exclamation_id || !npc->comp_npc.exclamation_display)
        return;
    id = npc->comp_npc.exclamation_id;
    world->entity[id].comp_render.is_visible = false;
    npc->comp_npc.exclamation_end = true;
}

static bool is_first(entity_t *player, entity_t *entity)
{
    int dialog = entity->comp_dialog.current_dialog;
    int sentence = entity->comp_dialog.current_sentence;
    int temp = 0;

    if (dialog == -1) {
        player->comp_position.can_move = !entity->comp_dialog.freeze_player;
        entity->comp_dialog.current_dialog = 0;
        entity->comp_dialog.current_char = 0;
        entity->comp_dialog.current_sentence = 0;
        temp += 1;
    }
    if (sentence == -1) {
        player->comp_position.can_move = !entity->comp_dialog.freeze_player;
        entity->comp_dialog.current_sentence = 0;
        entity->comp_dialog.current_char = 0;
        temp += 1;
    }
    if (temp)
        return true;
    return false;
}

static void update_npc_direction(entity_t *npc, entity_t *player)
{
    sfVector2f scale = sfSprite_getScale(npc->comp_render.sprite);

    if (npc->comp_position.position.x > player->comp_position.position.x)
        scale.x = abs(scale.x) * -1;
    else
        scale.x = abs(scale.x);
    sfSprite_setScale(npc->comp_render.sprite, scale);
}

static void give_item(world_t *world, entity_t *npc, entity_t *player)
{
    if (npc->comp_npc.gives_item == false)
        return;
    if (npc->comp_npc.gives_item_dialog_id != npc->comp_dialog.current_dialog)
        return;
    if (npc->comp_npc.gives_item_sentence_id !=
        npc->comp_dialog.current_sentence)
        return;
    npc->comp_npc.gives_item = false;
    create_item(world, player->comp_position.position, npc->comp_npc.item_id);
}

void update_dialog(win_t *window, world_t *world, entity_t *entity)
{
    int dialog = entity->comp_dialog.current_dialog;
    int sentence = entity->comp_dialog.current_sentence;
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    if (entity->comp_dialog.is_finished) {
        player->comp_position.can_move = true;
        return;
    }
    player->comp_position.can_move = !entity->comp_dialog.freeze_player;
    update_npc_direction(entity, player);
    give_item(world, entity, player);
    if (is_first(player, entity))
        return delete_mark(world, entity);
    if (entity->comp_dialog.current_char < strlen(
        entity->comp_dialog.text[dialog][sentence])) {
        entity->comp_dialog.current_char += 1;
        return;
    }
    mini_update_dialog(window, world, entity);
}
