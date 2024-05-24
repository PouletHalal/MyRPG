/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys render
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <math.h>
#include "temp.h"
#include "rendering.h"
#include "player.h"

void add_effect(world_t *world, entity_t *entity, enum effect effect_index)
{
    for (int i = 0; i < MAX_EFFECT; i++){
        if (entity->comp_stat.effect[i] == NULL){
            entity->comp_stat.effect[i] = &world->effect_list[effect_index];
            entity->comp_stat.effect_duration[i] =
                world->effect_list[effect_index].duration;
            entity->comp_stat.effect_tick_cooldown[i] =
                world->effect_list[effect_index].base_tick_cooldown;
            return;
        }
    }
}

static void execute_effect(entity_t *entity, effect_t *effect, int i)
{
    entity->comp_stat.effect_duration[i] -= 1;
    entity->comp_stat.effect_tick_cooldown[i] -= 1;
    if (entity->comp_stat.effect_duration[i] < 0){
        entity->comp_stat.effect[i] = NULL;
        return;
    }
    if (entity->comp_stat.effect_tick_cooldown[i] > 0)
        return;
    entity->comp_stat.effect_tick_cooldown[i] = effect->base_tick_cooldown;
    if (effect->effect_type == HEAL)
        entity->comp_stat.health += effect->value;
    if (effect->effect_type == DAMAGE)
        entity->comp_stat.health -= effect->value;
}

void loop_effect(entity_t *entity)
{
    for (int i = 0; i < MAX_EFFECT; i++)
        if (entity->comp_stat.effect[i] != NULL)
            execute_effect(entity, entity->comp_stat.effect[i], i);
}
