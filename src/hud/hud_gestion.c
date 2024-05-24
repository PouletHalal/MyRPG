/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** hud_gestion
*/

#include "world.h"
#include "hud.h"

static void update_xpbar(world_t *world, int i, entity_t *player)
{
    world->entity[i].comp_render.current_animation->base_text_rect.width =
    world->animations[get_anim_id(world, "xpbar")].frame_size.x *
    player->comp_stat.exp / player->comp_stat.exp_requiered;
    sfSprite_setTextureRect(world->entity[i].comp_render.sprite,
    world->entity[i].comp_render.current_animation->base_text_rect);
}

static void update_manabar(world_t *world, int i, entity_t *player)
{
    world->entity[i].comp_render.current_animation->base_text_rect.width =
    world->animations[get_anim_id(world, "manabar")].frame_size.x *
    player->comp_stat.mana / player->comp_stat.mana_max;
    sfSprite_setTextureRect(world->entity[i].comp_render.sprite,
    world->entity[i].comp_render.current_animation->base_text_rect);
}

void update_hud(world_t *world, entity_t *player)
{
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if ((world->entity[i].mask & COMP_HUD) == COMP_HUD &&
            world->entity[i].comp_hud.hud_type == HUD_HEALTHBAR) {
            update_healthbar(world, i, player);
        }
        if ((world->entity[i].mask & COMP_HUD) == COMP_HUD &&
            world->entity[i].comp_hud.hud_type == HUD_XPBAR) {
            update_xpbar(world, i, player);
        }
        if ((world->entity[i].mask & COMP_HUD) == COMP_HUD &&
            world->entity[i].comp_hud.hud_type == HUD_MANABAR) {
            update_manabar(world, i, player);
        }
    }
}

void update_healthbar(world_t *world, int i, entity_t *player)
{
    world->entity[i].comp_render.current_animation->base_text_rect.width =
    world->animations[get_anim_id(world, "healthbar")].frame_size.x *
    player->comp_stat.health / player->comp_stat.max_health;
    sfSprite_setTextureRect(world->entity[i].comp_render.sprite,
    world->entity[i].comp_render.current_animation->base_text_rect);
}
