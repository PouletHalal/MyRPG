/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** read_config
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"
#include "maps.h"
#include "camera.h"
#include "rendering.h"
#include "error_handling.h"
#include "sounds.h"
#include "player.h"
#include "mouse.h"
#include "hud.h"
#include "ui.h"

void read_configs(world_t *world, win_t *window)
{
    sfVector2f position_player = {636, 489};
    int anim_index = get_anim_id(world, "prota_idle");

    init_entity(world, &world->animations[anim_index],
    position_player);
    read_effect_conf(world);
    read_spells_conf(world);
    read_items_conf(world);
    init_healthbar(world);
    init_xpbar(world);
    init_manabar(world);
    read_npcconf(world);
    read_portalconf(world);
    read_mobconf(world);
    read_partconf(world);
    init_cam(window, world, &world->entity[find_comp(world, COMP_PLAYER)]);
    init_mouse(world, window);
    read_ui_conf(world);
}
