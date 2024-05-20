/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Animation file
*/

#include <string.h>
#include "temp.h"
#include "rendering.h"

int get_anim_id(world_t *world, char *name)
{
    for (int i = 0; world->animations[i].filename != NULL; i++) {
        if (strcmp(name, world->animations[i].name) == 0)
            return i;
    }
    return -1;
}

void update_sprite_direction(entity_t *entity)
{
    comp_render_t *c_render = &(entity->comp_render);
    sfSprite *sprite = c_render->sprite;
    sfVector2f scale = sfSprite_getScale(c_render->sprite);
    sfVector2f velocity = get_mouv_vector(entity);

    if (scale.x < 0 && velocity.x > 0 || scale.x > 0 && velocity.x < 0)
        sfSprite_setScale(sprite, (sfVector2f){scale.x * -1, scale.y});
}

bool is_in_animation(entity_t *entity)
{
    comp_render_t *c_render = &(entity->comp_render);
    animation_t *anim = c_render->current_animation;

    if (c_render->does_loop == true)
        return false;
    if (c_render->act_frame >= anim->frame_count)
        return false;
    return true;
}

void play_animation(world_t *world, entity_t *entity, int animation_index,
    sfBool does_loop)
{
    comp_render_t *c_render = NULL;
    animation_t *anim = NULL;
    sfIntRect *rect = NULL;
    float mult_scale = 0;

    if (animation_index == -1)
        animation_index = 0;
    c_render = &(entity->comp_render);
    anim = &world->animations[animation_index];
    rect = &(anim->base_text_rect);
    mult_scale = (sfSprite_getScale(c_render->sprite).x < 0 ? -1 : 1);
    if (c_render->current_animation == anim && c_render->does_loop == true)
        return;
    c_render->current_animation = anim;
    c_render->act_frame = 0;
    c_render->clock = 0;
    c_render->does_loop = does_loop;
    c_render->is_visible = true;
    c_render->texture = c_render->texture_list[animation_index];
    set_sprite(entity, anim, mult_scale, rect);
}

void set_sprite(entity_t *entity, animation_t *anim,
    float mult_scale, sfIntRect *rect)
{
    comp_render_t *c_render = &(entity->comp_render);

    sfSprite_setTexture(c_render->sprite, c_render->texture, sfFalse);
    sfSprite_setPosition(c_render->sprite, entity->comp_position.position);
    sfSprite_setScale(c_render->sprite,
    (sfVector2f){anim->scale.x * mult_scale, anim->scale.x});
    sfSprite_setTextureRect(c_render->sprite, anim->base_text_rect);
    sfSprite_setOrigin(c_render->sprite,
    (sfVector2f){rect->width / 2, rect->height / 2});
}
