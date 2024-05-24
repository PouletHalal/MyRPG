/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys render
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "temp.h"
#include "camera.h"
#include <string.h>

static void update_texture_rect(comp_render_t *c_render)
{
    animation_t *anim = c_render->current_animation;
    sfVector2u sheet_size = sfTexture_getSize(c_render->texture);
    int frame_per_line = sheet_size.x / anim->frame_size.x;
    sfIntRect rect = {0};

    rect.left = anim->base_text_rect.left + anim->frame_size.x *
    (c_render->act_frame % frame_per_line);
    rect.top = anim->base_text_rect.top + anim->frame_size.y *
    (c_render->act_frame / frame_per_line);
    rect.width = anim->frame_size.x;
    rect.height = anim->frame_size.y;
    sfSprite_setTextureRect(c_render->sprite, rect);
}

static void next_frame(entity_t *entity, world_t *world)
{
    comp_render_t *c_render = &entity->comp_render;
    animation_t *anim = c_render->current_animation;

    sfSprite_setPosition(c_render->sprite, entity->comp_position.position);
    if (c_render->clock < anim->frame_rate){
        c_render->clock += 1;
        return;
    }
    c_render->clock = 0;
    c_render->act_frame += 1;
    if (c_render->act_frame >= anim->frame_count)
        if (c_render->does_loop == false)
            return;
        else
            c_render->act_frame = 0;
    if (strcmp(c_render->current_animation->filename,
        "effect/mob_healthbar.png") == 0)
        return;
    update_texture_rect(c_render);
}

sfBool has_comp(entity_t *entity, int comp)
{
    if ((entity->mask & comp) == comp)
        return sfTrue;
    return sfFalse;
}

void sys_render(win_t *window, world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i) {
        if (has_comp(&world->entity[i], COMP_RENDER) &&
        world->entity[i].comp_position.world == world->map_id &&
        (is_in_cam_range(window, &world->entity[i]) ||
        has_comp(&world->entity[i], COMP_HUD) ||
        has_comp(&world->entity[i], COMP_ITEM)))
            next_frame(&world->entity[i], world);
        if (world->is_paused && has_comp(&world->entity[i], COMP_RENDER)
            && has_comp(&world->entity[i], COMP_UI))
            next_frame(&world->entity[i], world);
    }
}
