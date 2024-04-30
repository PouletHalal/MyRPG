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
    sfVector2f position, const sprite_info_t *mob)
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
    entity->mask |= COMP_RENDER;
    entity->comp_render.is_visible = true;
    entity->comp_render.does_loop = true;
    entity->comp_render.frame_count = mob->frame_count;
    entity->comp_render.clock = 0;
    entity->comp_render.frame_size = mob->frame_size;
    entity->comp_render.frame_rate = 60 / mob->frame_rate;
}

void init_entity(entity_t *entity,
    sfTexture *texture, const sprite_info_t *mob, world_t *world)
{
    sfVector2f position = {96, 96};
    sfFloatRect rect;

    *entity = (entity_t) {0};
    init_comp_render(entity, texture, position, mob);
    entity->mask |= COMP_POSITION | COMP_INPUT | COMP_PLAYER | COMP_HITBOX;
    entity->comp_input.key_pressed = world->key_pressed;
    entity->comp_position.position = position;
    entity->comp_hitbox.do_collide = sfTrue;
    entity->comp_render.starting_rect = mob->text_rect;
    sfSprite_setScale(entity->comp_render.sprite, mob->scale);
    rect = sfSprite_getGlobalBounds(entity->comp_render.sprite);
    entity->comp_hitbox.hitbox = (sfFloatRect)
    {rect.left + rect.width / 4. - position.x,
    rect.top + rect.height / 4. - position.y,
    rect.width / 2., rect.height / 2.};
}

static void init_comp_mob(entity_t *entity, enum texture_list mob)
{
    entity->comp_mob.is_alive = sfTrue;
    entity->comp_mob.range = 200.;
    entity->comp_mob.speed = 1.;
    entity->comp_mob.does_follow = sfTrue;
    entity->comp_render.starting_rect = mob_list[mob].text_rect;
}

static void init_hitbox(entity_t *entity, sfVector2f position)
{
    sfFloatRect rect;

    rect = sfSprite_getGlobalBounds(entity->comp_render.sprite);
    entity->comp_hitbox.hitbox = (sfFloatRect)
    {rect.left + rect.width / 4. - position.x,
    rect.top + rect.height / 4. - position.y,
    rect.width / 2., rect.height / 2.};
}

void init_mob(enum texture_list mob, world_t *world,
    sfVector2f position)
{
    int free = find_empty(world);
    entity_t *entity;

    if (free == -1)
        return;
    entity = &world->entity[free];
    *entity = (entity_t) {0};
    entity->entity = free;
    init_comp_render(entity, world->texture_list[mob],
    position, &mob_list[mob]);
    entity->mask |= COMP_POSITION | COMP_MOB | COMP_HITBOX;
    entity->comp_position.position = position;
    entity->comp_hitbox.do_collide = sfTrue;
    sfSprite_setScale(entity->comp_render.sprite, mob_list[mob].scale);
    init_hitbox(entity, position);
    init_comp_mob(entity, mob);
}
