/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** components_inits
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
    (sfVector2f) {rect->width / 2, rect->height / 2});
}

void init_comp_hitbox(entity_t *entity, sfVector2f position)
{
    sfFloatRect rect;

    entity->mask |= COMP_HITBOX;
    rect = sfSprite_getGlobalBounds(entity->comp_render.sprite);
    entity->comp_hitbox.do_collide = sfTrue;
    entity->comp_hitbox.hitbox = (sfFloatRect)
    {rect.left + rect.width / 4. - position.x,
    rect.top + rect.height / 4. - position.y,
    rect.width / 2., rect.height / 2.};
    entity->comp_hitbox.do_collide = sfTrue;
}

void init_comp_mob(entity_t *entity)
{
    entity->mask |= COMP_MOB;
    entity->comp_mob.is_alive = sfTrue;
    entity->comp_mob.range = 200.;
    entity->comp_mob.speed = 1.;
    entity->comp_mob.does_follow = sfTrue;
}

void init_comp_input(entity_t *entity, world_t *world)
{
    entity->mask |= COMP_INPUT;
    entity->comp_input.key_pressed = world->key_pressed;
    entity->comp_input.key_down = world->key_down;
}

void init_comp_position(entity_t *entity, sfVector2f position, int world_id)
{
    entity->mask |= COMP_POSITION;
    entity->comp_position.position = position;
    entity->comp_position.can_move = sfTrue;
    entity->comp_position.spawn = position;
    entity->comp_position.world = world_id;
}
