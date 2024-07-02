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
void init_xpbar(world_t *world);
void update_hud(world_t *world, entity_t *player);
void init_manabar(world_t *world);
void update_healthbar(world_t *world, int i, entity_t *player);

#endif /* !HUD_H_ */
