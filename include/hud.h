/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** hud
*/

#ifndef HUD_H_
    #define HUD_H_

    #include "world.h"

void init_healthbar(world_t *world);
void place_bar(entity_t *hb, world_t *world, int anim_id);
void update_hud(world_t *world, entity_t *player);

#endif /* !HUD_H_ */
