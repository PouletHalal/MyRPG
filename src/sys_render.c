/*
** EPITECH PROJECT, 2024
** My_rpg
** File description:
** Sys Render file
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "temp.h"

static void update_texture_rect(comp_render_t *c_render)
{
    sfIntRect rect = {0};
    sfVector2u sheet_size = sfTexture_getSize(c_render->texture);
    int frame_per_line = sheet_size.x / c_render->frame_size.x;

    rect.left = c_render->starting_rect.left + c_render->frame_size.x * (c_render->frame % frame_per_line);
    rect.top = c_render->starting_rect.top + c_render->frame_size.y * (c_render->frame / frame_per_line);
    rect.width = c_render->frame_size.x;
    rect.height = c_render->frame_size.y;
    sfSprite_setTextureRect(c_render->sprite, rect);
}

static void next_frame(entity_t *entity)
{
    comp_render_t *c_render = &entity->comp_render;

    sfSprite_setPosition(c_render->sprite, entity->comp_position.position);
    if (c_render->clock < c_render->frame_rate){
        c_render->clock += 1;
        return;
    }
    c_render->clock = 0;
    c_render->frame += 1;
    if (c_render->frame >= c_render->frame_count)
        if (c_render->does_loop == false) {
            c_render->is_visible = false;
            entity->mask = COMP_NONE;
            sfSprite_destroy(c_render->sprite);
            return;
        } else
            c_render->frame = 0;
    update_texture_rect(c_render);
}

void sys_render(world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask & COMP_RENDER == COMP_RENDER)
            next_frame(&world->entity[i]);
}
