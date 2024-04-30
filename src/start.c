/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Start file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"

void init_comp_render(entity_t *entity, world_t *world,
    enum anim_list anim_nbr, sfVector2f position)
{
    comp_render_t *c_render = &(entity->comp_render);
    animation_t *anim = &(animation_list[anim_nbr]);
    sfIntRect *rect = &(anim->base_text_rect);

    entity->mask |= COMP_RENDER;
    c_render->current_animation = anim;
    c_render->act_frame = 0;
    c_render->clock = 0;
    c_render->does_loop = true;
    c_render->is_visible = true;
    c_render->sprite = sfSprite_create();
    c_render->texture = world->texture_list[anim_nbr];
    sfSprite_setTexture(c_render->sprite, c_render->texture, sfFalse);
    sfSprite_setPosition(c_render->sprite, position);
    sfSprite_setScale(c_render->sprite, anim->scale);
    sfSprite_setTextureRect(c_render->sprite, anim->base_text_rect);
    sfSprite_setOrigin(c_render->sprite,
        (sfVector2f){rect->width / 2, rect->height / 2});
}

void init_entity(world_t *world, enum anim_list anim_nbr, sfVector2f position)
{
    sfFloatRect rect;
    int free = find_empty(world);
    entity_t *entity;

    if (free == -1)
        return;
    entity = &world->entity[free];
    *entity = (entity_t){0};
    entity->entity = free;
    entity->mask |= COMP_POSITION | COMP_INPUT | COMP_PLAYER | COMP_HITBOX;
    init_comp_render(entity, world, anim_nbr, position);
    entity->comp_position.position = position;
    entity->comp_position.velocity.x = 0;
    entity->comp_position.velocity.y = 0;
    entity->comp_input.key_pressed = world->key_pressed;
    entity->comp_hitbox.do_collide = sfTrue;
    rect = sfSprite_getGlobalBounds(entity->comp_render.sprite);
    entity->comp_hitbox.hitbox = (sfFloatRect)
    {rect.left + rect.width / 4. - position.x,
    rect.top + rect.height / 4. - position.y,
    rect.width / 2., rect.height / 2.};
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

static void init_comp_mob(entity_t *entity)
{
    entity->mask |= COMP_MOB;
    entity->comp_mob.is_alive = sfTrue;
    entity->comp_mob.range = 200.;
    entity->comp_mob.speed = 1.;
    entity->comp_mob.does_follow = sfTrue;
}

void init_mob(world_t *world, enum anim_list anim_nbr, sfVector2f position)
{
    sfFloatRect rect;
    int free = find_empty(world);
    entity_t *entity;

    if (free == -1)
        return;
    entity = &world->entity[free];
    *entity = (entity_t){0};
    entity->entity = free;
    entity->mask |= COMP_POSITION | COMP_HITBOX;
    init_comp_render(entity, world, anim_nbr, position);
    init_comp_mob(entity);
    entity->comp_hitbox.do_collide = sfTrue;
    entity->comp_position.position = position;
    entity->comp_position.velocity.x = 0;
    entity->comp_position.velocity.y = 0;
    rect = sfSprite_getGlobalBounds(entity->comp_render.sprite);
    entity->comp_hitbox.hitbox = (sfFloatRect){
    rect.left + rect.width / 4. - position.x,
    rect.top + rect.height / 4. - position.y,
    rect.width / 2., rect.height / 2.};
}