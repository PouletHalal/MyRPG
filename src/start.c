/*
** EPITECH PROJECT, 2024
** My radar
** File description:
** Start file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"

static void init_comp_render(entity_t *entity, sfTexture *texture,
    sfVector2f position, sprite_info_t *mob)
{
    int ran = rand();

    entity->comp_render.frame = 0;
    entity->comp_render.sprite = sfSprite_create();
    entity->comp_render.texture = texture;
    sfSprite_setTexture(entity->comp_render.sprite,
    entity->comp_render.texture, sfFalse);
    sfSprite_setOrigin(entity->comp_render.sprite,
    (sfVector2f) {mob->text_rect.width / 2, mob->text_rect.height / 2});
    sfSprite_setScale(entity->comp_render.sprite,
    (sfVector2f) {0.5 + ran % 1, 0.5 + ran % 1});
    sfSprite_setPosition(entity->comp_render.sprite, position);
    sfSprite_setTextureRect(entity->comp_render.sprite, mob->text_rect);
    entity->mask = COMP_RENDER | COMP_POSITION | COMP_INPUT | COMP_PLAYER;
    entity->comp_render.is_visible = true;
    entity->comp_render.does_loop = true;
    entity->comp_render.frame_count = mob->frame_count;
    entity->comp_render.clock = 0;
    entity->comp_render.frame_size = mob->frame_size;
    entity->comp_render.frame_rate = 60 / mob->frame_rate;
}

void init_entity(entity_t *entity,
    sfTexture *texture, sprite_info_t *mob, world_t *world)
{
    sfVector2f position = {96, 96};

    init_comp_render(entity, texture, position, mob);
    entity->comp_input.key_pressed = world->key_pressed;
    entity->comp_position.position = position;
    entity->comp_render.starting_rect = mob->text_rect;
    sfSprite_setScale(entity->comp_render.sprite, mob->scale);
}
