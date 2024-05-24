/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** init_hud
*/

#include "world.h"
#include "temp.h"
#include "player.h"
#include "hud.h"

static void init_heart(world_t *world)
{
    int free_slot = find_empty(world);
    entity_t *heart = NULL;
    int anim_id = get_anim_id(world, "spinning_heart");
    animation_t *anim = NULL;

    if (free_slot < 0)
        return;
    if (anim_id < 0)
        anim_id = 0;
    anim = &world->animations[anim_id];
    heart = &world->entity[free_slot];
    heart->entity = free_slot;
    init_comp_render(heart, world, &world->animations[anim_id],
    (sfVector2f) {0});
    init_comp_position(heart, (sfVector2f){anim->base_text_rect.width / 2 *
    anim->scale.x - 60,
    anim->base_text_rect.height / 2 * anim->scale.y - 40}, 2);
    heart->mask |= COMP_HUD;
}

static void init_plate(world_t *world)
{
    int free_slot = find_empty(world);
    entity_t *hb = NULL;
    int anim_id = get_anim_id(world, "healthbar_plate");

    if (free_slot < 0)
        return;
    if (anim_id < 0)
        anim_id = 0;
    hb = &world->entity[free_slot];
    hb->entity = free_slot;
    init_comp_render(hb, world, &world->animations[anim_id], (sfVector2f) {0});
    init_comp_position(hb, (sfVector2f){120 +
        hb->comp_render.current_animation->base_text_rect.width *
        hb->comp_render.current_animation->scale.x / 2,
        hb->comp_render.current_animation->base_text_rect.height *
        hb->comp_render.current_animation->scale.y / 2 + 10}, 2);
    hb->mask |= COMP_HUD;
    hb->comp_hud.hud_type = HUD_PLATE;
}

static void place_bar(entity_t *hb, world_t *world, int anim_id)
{
    init_comp_render(hb, world, &world->animations[anim_id], (sfVector2f){0});
    init_comp_position(hb, (sfVector2f)
    {120 + 8 + hb->comp_render.current_animation->base_text_rect.width *
    hb->comp_render.current_animation->scale.x / 2,
    hb->comp_render.current_animation->base_text_rect.height *
    hb->comp_render.current_animation->scale.y / 2 + 40}, 2);
}

static void init_px_plate(world_t *world)
{
    int free_slot = find_empty(world);
    entity_t *hb = NULL;
    int anim_id = get_anim_id(world, "xpbar_plate");

    if (free_slot < 0)
        return;
    if (anim_id < 0)
        anim_id = 0;
    hb = &world->entity[free_slot];
    hb->entity = free_slot;
    init_comp_render(hb, world, &world->animations[anim_id], (sfVector2f) {0});
    init_comp_position(hb, (sfVector2f){120 +
        hb->comp_render.current_animation->base_text_rect.width *
        hb->comp_render.current_animation->scale.x / 2,
        hb->comp_render.current_animation->base_text_rect.height *
        hb->comp_render.current_animation->scale.y / 2 + 100}, 2);
    hb->mask |= COMP_HUD;
    hb->comp_hud.hud_type = HUD_PLATE;
}

static void place_xp_bar(entity_t *hb, world_t *world, int anim_id)
{
    init_comp_render(hb, world, &world->animations[anim_id], (sfVector2f){0});
    init_comp_position(hb, (sfVector2f)
    {120 + 2 + hb->comp_render.current_animation->base_text_rect.width *
    hb->comp_render.current_animation->scale.x / 2,
    hb->comp_render.current_animation->base_text_rect.height *
    hb->comp_render.current_animation->scale.y / 2 + 115}, 2);
}

void init_healthbar(world_t *world)
{
    int free_slot = find_empty(world);
    entity_t *hb = NULL;
    int anim_id = get_anim_id(world, "healthbar");
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    if (free_slot < 0)
        return;
    if (anim_id < 0)
        anim_id = 0;
    hb = &world->entity[free_slot];
    hb->entity = free_slot;
    place_bar(hb, world, anim_id);
    hb->mask |= COMP_HUD;
    hb->comp_render.current_animation->base_text_rect.width =
    world->animations[anim_id].base_text_rect.width;
    sfSprite_setTextureRect(hb->comp_render.sprite,
    world->animations[anim_id].base_text_rect);
    hb->comp_hud.hud_type = HUD_HEALTHBAR;
    init_plate(world);
    init_heart(world);
}

void init_xpbar(world_t *world)
{
    int free_slot = find_empty(world);
    entity_t *xp = NULL;
    int anim_id = get_anim_id(world, "xpbar");
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    if (free_slot < 0)
        return;
    if (anim_id < 0)
        anim_id = 0;
    xp = &world->entity[free_slot];
    xp->entity = free_slot;
    place_xp_bar(xp, world, anim_id);
    xp->mask |= COMP_HUD;
    xp->comp_render.current_animation->base_text_rect.width =
    world->animations[anim_id].base_text_rect.width;
    sfSprite_setTextureRect(xp->comp_render.sprite,
    world->animations[anim_id].base_text_rect);
    xp->comp_hud.hud_type = HUD_XPBAR;
    init_px_plate(world);
}

static void init_mana_plate(world_t *world)
{
    int free_slot = find_empty(world);
    entity_t *hb = NULL;
    int anim_id = get_anim_id(world, "xpbar_plate");

    if (free_slot < 0)
        return;
    if (anim_id < 0)
        anim_id = 0;
    hb = &world->entity[free_slot];
    hb->entity = free_slot;
    init_comp_render(hb, world, &world->animations[anim_id], (sfVector2f) {0});
    init_comp_position(hb, (sfVector2f){320 +
        hb->comp_render.current_animation->base_text_rect.width *
        hb->comp_render.current_animation->scale.x / 2,
        hb->comp_render.current_animation->base_text_rect.height *
        hb->comp_render.current_animation->scale.y / 2 + 100}, 2);
    hb->mask |= COMP_HUD;
    hb->comp_hud.hud_type = HUD_PLATE;
}

static void place_mana_bar(entity_t *hb, world_t *world, int anim_id)
{
    init_comp_render(hb, world, &world->animations[anim_id], (sfVector2f){0});
    init_comp_position(hb, (sfVector2f)
    {320 + 2 + hb->comp_render.current_animation->base_text_rect.width *
    hb->comp_render.current_animation->scale.x / 2,
    hb->comp_render.current_animation->base_text_rect.height *
    hb->comp_render.current_animation->scale.y / 2 + 115}, 2);
}

void init_manabar(world_t *world)
{
    int free_slot = find_empty(world);
    entity_t *hb = NULL;
    int anim_id = get_anim_id(world, "manabar");
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    if (free_slot < 0)
        return;
    if (anim_id < 0)
        anim_id = 0;
    hb = &world->entity[free_slot];
    hb->entity = free_slot;
    place_mana_bar(hb, world, anim_id);
    hb->mask |= COMP_HUD;
    hb->comp_render.current_animation->base_text_rect.width =
    world->animations[anim_id].base_text_rect.width;
    sfSprite_setTextureRect(hb->comp_render.sprite,
    world->animations[anim_id].base_text_rect);
    hb->comp_hud.hud_type = HUD_MANABAR;
    init_mana_plate(world);
}
