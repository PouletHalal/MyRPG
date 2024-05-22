/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Start file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"

void init_spell(world_t *world, sfVector2f position, enum spell spell_nbr)
{
    int free = find_empty(world);
    entity_t *entity;

    if (free == -1)
        return;
    entity = &world->entity[free];
    *entity = (entity_t){0};
    entity->entity = free;
    init_comp_position(entity, position, world->map_id);
    init_comp_render(entity, world, spell_list[spell_nbr].index, position);
    init_comp_hitbox(entity, position);
    entity->mask |= COMP_SPELL;
    entity->comp_hitbox.do_collide = sfFalse;
    entity->comp_spell = spell_list[spell_nbr];
    if (entity->comp_spell.move_type == DIRECT){
        follow_enemy(entity, get_closest(entity, world));
        entity->comp_position.vector_lenght[0] = 9999999;
    }
}
