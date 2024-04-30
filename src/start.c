/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Start file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"

static void init_comp_render(entity_t *entity, world_t *world, enum anim_list anim_nbr,
    sfVector2f position)
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

void init_entity(entity_t *entity, world_t *world, enum anim_list anim_nbr, sfVector2f position)
{
    *entity = (entity_t) {0};
    entity->mask |= COMP_POSITION | COMP_INPUT | COMP_PLAYER;
    init_comp_render(entity, world, anim_nbr, position);
    entity->comp_position.position = position;
    entity->comp_position.velocity.x = 0;
    entity->comp_position.velocity.y = 0;
    entity->comp_input.key_pressed = world->key_pressed;
}

void init_mob(entity_t *entity, world_t *world, enum anim_list anim_nbr, sfVector2f position)
{
    *entity = (entity_t){0};
    entity->mask |= COMP_POSITION | COMP_MOB;
    init_comp_render(entity, world, anim_nbr, position);
    entity->comp_mob.does_follow = sfTrue;
    entity->comp_mob.does_take_damage = sfTrue;
    entity->comp_mob.is_alive = sfTrue;
    entity->comp_mob.range = 200;
    entity->comp_mob.speed = 1;
    entity->comp_position.position = position;
    entity->comp_position.velocity.x = 0;
    entity->comp_position.velocity.y = 0;
}
