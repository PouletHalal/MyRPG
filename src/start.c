/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Start file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"

void init_entity(world_t *world, animation_t *anim, sfVector2f position)
{
    int free = find_empty(world);
    entity_t *entity;

    if (free == -1)
        return;
    entity = &world->entity[free];
    *entity = (entity_t){0};
    entity->entity = free;
    entity->mask |= COMP_PLAYER | COMP_STAT;
    entity->comp_input.pressed_func[sfKeySpace] = &npc_collision;
    entity->comp_stat = (comp_stat_t)
    {FRIENDLY, 100., 50., 0.01, sfTrue, sfTrue, 30., 5., 0., 20.};
    init_comp_position(entity, position, world->map_id);
    init_comp_render(entity, world, anim, position);
    init_comp_hitbox(entity, position);
    init_comp_input(entity, world);
    init_inventory(world, entity, 18);
    entity->comp_position.can_move = true; 
}

void init_mob(world_t *world, animation_t *anim, sfVector2f position)
{
    int free = find_empty(world);
    entity_t *entity;

    if (free == -1)
        return;
    entity = &world->entity[free];
    *entity = (entity_t) {0};
    entity->entity = free;
    entity->mask |= COMP_STAT;
    entity->comp_stat = (comp_stat_t)
    {ENEMY, 30., 30., 0., sfTrue, sfTrue, 10., 5., 0., 20.};
    init_comp_position(entity, position, world->map_id);
    init_comp_render(entity, world, anim, position);
    init_comp_mob(entity);
    init_comp_hitbox(entity, position);
}
