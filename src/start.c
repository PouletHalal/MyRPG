/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Start file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"

void init_entity(world_t *world, enum anim_list anim_nbr, sfVector2f position)
{
    int free = find_empty(world);
    entity_t *entity;

    if (free == -1)
        return;
    entity = &world->entity[free];
    *entity = (entity_t){0};
    entity->entity = free;
    entity->mask |= COMP_PLAYER;
    init_comp_position(entity, position);
    init_comp_render(entity, world, anim_nbr, position);
    init_comp_hitbox(entity, position);
    init_comp_input(entity, world);
}

void init_mob(world_t *world, enum anim_list anim_nbr, sfVector2f position)
{
    int free = find_empty(world);
    entity_t *entity;

    if (free == -1)
        return;
    entity = &world->entity[free];
    *entity = (entity_t){0};
    entity->entity = free;
    init_comp_position(entity, position);
    init_comp_render(entity, world, anim_nbr, position);
    init_comp_mob(entity);
    init_comp_hitbox(entity, position);
}
