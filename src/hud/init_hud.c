/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_hud
*/

#include "world.h"

void init_healthbar(world_t *world)
{
    int free_slot = find_empty_slot(&world->entity[0]);
    entity_t *hb = NULL;

    if (free_slot < 0)
        return;
    hb = &world->entity[free_slot];
    init_comp_render(hb, world, ANIM_HEALTHBAR, (sfVector2f){0, 0});
    init_comp_position(hb, (sfVector2f){0, 0}, 0);
}
