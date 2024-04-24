/*
** EPITECH PROJECT, 2024
** My_rpg
** File description:
** Sys Render file
*/

#include <SFML/Graphics.h>
#include <SFML/Window/Keyboard.h>
#include <stdlib.h>
#include "temp.h"

static void update_speedx(entity_t *entity, int offset)
{
    sfVector2f scale = sfSprite_getScale(entity->comp_render.sprite);
    int new_scale_x = offset / abs(offset);
    
    entity->comp_render.starting_rect.top = 96;
    entity->comp_render.frame_count = 8;
    entity->comp_render.frame_rate = 60 / 5;
    entity->comp_position.velocity.x = offset;
    sfSprite_setScale(entity->comp_render.sprite, (sfVector2f) {abs(scale.x) * new_scale_x, scale.y});
}

static void update_speedy(entity_t *entity, int offset)
{
    entity->comp_render.starting_rect.top = 96;
    entity->comp_render.frame_count = 8;
    entity->comp_render.frame_rate = 60 / 5;
    entity->comp_position.velocity.y = offset;
}

static void next_frame(entity_t *entity)
{
    entity->comp_position.velocity.x = 0;
    entity->comp_position.velocity.y = 0;
    entity->comp_render.starting_rect.top = 0;
    entity->comp_render.frame_count = 2;
    entity->comp_render.frame_rate = 60 / 2;
    if (is_key_pressed(entity, sfKeyD))
        update_speedx(entity, 5);
    if (is_key_pressed(entity, sfKeyQ))
        update_speedx(entity, -5);
    if (is_key_pressed(entity, sfKeyS))
        update_speedy(entity, 5);
    if (is_key_pressed(entity, sfKeyZ))
        update_speedy(entity, -5);
}

void sys_player(world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask & COMP_PLAYER == COMP_PLAYER)
            next_frame(&world->entity[i]);
}
