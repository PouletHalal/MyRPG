/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys render
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "temp.h"

static void update_texture_rect(comp_render_t *c_render)
{
    animation_t *anim = c_render->current_animation;
    sfVector2u sheet_size = sfTexture_getSize(c_render->texture);
    int frame_per_line = sheet_size.x / anim->frame_size.x;
    sfIntRect rect = {0};

    rect.left = anim->base_text_rect.left + anim->frame_size.x * (c_render->act_frame % frame_per_line);
    rect.top = anim->base_text_rect.top + anim->frame_size.y * (c_render->act_frame / frame_per_line);
    rect.width = anim->frame_size.x;
    rect.height = anim->frame_size.y;
    sfSprite_setTextureRect(c_render->sprite, rect);
}

static void next_frame(entity_t *entity)
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
    update_texture_rect(c_render);
}

void sys_render(world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_RENDER) == COMP_RENDER)
            next_frame(&world->entity[i]);
}
