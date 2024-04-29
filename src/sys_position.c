/*
** EPITECH PROJECT, 2024
** My_rpg
** File description:
** Sys Render file
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "temp.h"

static sfBool do_rect_collide(sfFloatRect rect, sfFloatRect bis)
{
    if ((rect.left < bis.left && rect.left + rect.width < bis.left)
        || (rect.left > bis.left + bis.width &&
        rect.left + rect.width > bis.left + bis.width))
        return sfFalse;
    if ((rect.top < bis.top && rect.top + rect.height < bis.top)
        || (rect.top > bis.top + bis.height &&
        rect.top + rect.height > bis.top + bis.height))
        return sfFalse;
    return sfTrue;
}

static sfBool collide_entity(entity_t *entity, entity_t *bis,
sfVector2f velocity)
{
    sfFloatRect entity_hitbox = entity->comp_hitbox.hitbox;
    sfFloatRect bis_hitbox = bis->comp_hitbox.hitbox;

    if ((bis->mask & (COMP_POSITION & COMP_HITBOX))
    != COMP_POSITION & COMP_HITBOX)
        return sfFalse;
    entity_hitbox.left += entity->comp_position.position.x;
    entity_hitbox.left += velocity.x;
    entity_hitbox.top += entity->comp_position.position.y;
    entity_hitbox.top += velocity.y;
    bis_hitbox.left += bis->comp_position.position.x;
    bis_hitbox.top += bis->comp_position.position.y;
    if (do_rect_collide(entity_hitbox, bis_hitbox))
        return sfTrue;
    return sfFalse;
}

static sfBool check_collision(entity_t *entity, world_t *world,
    sfVector2f velocity)
{
    sfFloatRect hitbox = entity->comp_hitbox.hitbox;
    sfVector2f position = entity->comp_position.position;

    if (((entity->mask & COMP_HITBOX) != COMP_HITBOX)
    || !entity->comp_hitbox.do_collide)
        return sfFalse;
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if (entity->entity != i &&
        collide_entity(entity, &world->entity[i], velocity))
            return sfTrue;
    return sfFalse;
}

static void next_frame(entity_t *entity, world_t *world)
{
    if (!check_collision(entity, world,
        (sfVector2f) {entity->comp_position.velocity.x, 0.}))
            entity->comp_position.position.x += entity->comp_position.velocity.x;
    if (!check_collision(entity, world,
        (sfVector2f) {0., entity->comp_position.velocity.y}))
            entity->comp_position.position.y += entity->comp_position.velocity.y;
}

void sys_position(world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_POSITION) == COMP_POSITION)
            next_frame(&world->entity[i], world);
}
