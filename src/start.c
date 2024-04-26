/*
** EPITECH PROJECT, 2024
** My_rpg
** File description:
** Start file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"

void create_perso_style_insane(entity_t *entity, world_t *world)
{
    sfVector2f position = {rand() % 1930 - 10, rand() % 1090 - 10};
    comp_render_t *c_render = &(entity->comp_render);
    animation_t *anim = &(animation_list[ANIM_PROTA_IDLE]);
    sfIntRect *rect = &(anim->base_text_rect);

    entity->mask = COMP_RENDER | COMP_POSITION | COMP_INPUT | COMP_PLAYER;
    c_render->current_animation = anim;
    c_render->act_frame = 0;
    c_render->clock = 0;
    c_render->does_loop = true;
    c_render->is_visible = true;
    c_render->sprite = sfSprite_create();
    c_render->texture = world->texture_list[ANIM_PROTA_IDLE];
    sfSprite_setTexture(c_render->sprite, c_render->texture, sfFalse);
    sfSprite_setPosition(c_render->sprite, position);
    sfSprite_setScale(c_render->sprite, anim->scale);
    sfSprite_setTextureRect(c_render->sprite, anim->base_text_rect);
    sfSprite_setOrigin(c_render->sprite,
        (sfVector2f){rect->width / 2, rect->height / 2});
    entity->comp_position.position = position;
    entity->comp_position.velocity.x = 5;
    entity->comp_position.velocity.y = 5;
    entity->comp_input.key_pressed = world->key_pressed;
}
