/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** hud_gestion
*/

#include "world.h"
#include "hud.h"

void update_hud(world_t *world, entity_t *player)
{
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if ((world->entity[i].mask & COMP_HUD) == COMP_HUD &&
            world->entity[i].comp_hud.hud_type == HUD_HEALTHBAR) {
                world->entity[i].comp_render.current_animation->base_text_rect.
                width = world->animations[get_anim_id(world, "healthbar")].
                frame_size.x * player->comp_stat.health /
                player->comp_stat.max_health;
                sfSprite_setTextureRect(world->entity[i].comp_render.sprite,
                world->entity[i].comp_render.current_animation->
                base_text_rect);
        }
    }
}
