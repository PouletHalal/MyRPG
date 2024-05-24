/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** sys_npc
*/

#include "temp.h"
#include "maps.h"
#include "player.h"
#include "rendering.h"
#include "camera.h"
#include "dialogs.h"
#include "hud.h"

static void init_mark(world_t *world, entity_t *player, entity_t *npc)
{
    entity_t *mark = NULL;
    int free_slot = find_empty(world);

    if (free_slot == -1)
        return;
    mark = &world->entity[free_slot];
    npc->comp_npc.exclamation_id = free_slot;
    init_comp_render(mark, world, &world->animations[get_anim_id(world,
        "exclamation")], (sfVector2f) {npc->comp_position.position.x,
        npc->comp_position.position.y - 30});
    init_comp_position(mark, (sfVector2f) {npc->comp_position.position.x,
        npc->comp_position.position.y - 30}, world->map_id);
    mark->comp_position.can_move = false;
    mark->comp_render.is_visible = true;
}

static void display_exclamation_mark(world_t *world, entity_t *player,
    entity_t *npc)
{
    if (npc->comp_npc.exclamation_id == 0)
        return init_mark(world, player, npc);
    if (npc->comp_npc.need_key_item_to_talk == false)
        npc->comp_npc.exclamation_end = true;
    if (npc->comp_npc.exclamation_end == true)
        return;
    if (npc->comp_npc.exclamation_display == true) {
        if (!is_in_inv(world, player, npc->comp_npc.key_item_to_talk_id))
            world->entity[npc->comp_npc.exclamation_id].comp_render.is_visible
            = false;
        else
            world->entity[npc->comp_npc.exclamation_id].comp_render.is_visible
            = true;
        return;
    }
}

void sys_npc(win_t *window, world_t *world, entity_t *player)
{
    entity_t *npc = NULL;

    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if (world->entity[i].comp_position.world != world->map_id)
            continue;
        npc = &world->entity[i];
        if ((npc->mask & COMP_DIALOG) == COMP_DIALOG &&
            (npc->mask & COMP_NPC) == COMP_NPC &&
            npc->comp_npc.need_key_item_to_talk) {
                display_exclamation_mark(world, player, npc);
        }
    }
}
