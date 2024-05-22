/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys stat
*/

#include "temp.h"
#include "rendering.h"

void do_attack(world_t *world, entity_t *attack, entity_t *defense)
{
    if ((attack->mask & defense->mask & COMP_STAT) != COMP_STAT)
        return;
    if (defense->comp_stat.clock > 0 || attack->comp_mob.does_rand_spawn ||
    defense->comp_mob.does_rand_spawn)
        return;
    if (attack->comp_stat.do_damage == sfFalse)
        return;
    if (attack->comp_stat.faction == defense->comp_stat.faction ||
    defense->comp_stat.defense > attack->comp_stat.damage)
        return;
    defense->comp_stat.health -=
    attack->comp_stat.damage - defense->comp_stat.defense;
    defense->comp_stat.clock = defense->comp_stat.invinsibility_frames;
    if ((defense->mask & COMP_PLAYER) == COMP_PLAYER)
        play_animation(world, defense, get_anim_id(world, "prota_hurt"), 0);
}

static void next_frame(win_t *window, entity_t *entity, world_t *world)
{
    comp_stat_t *stat = &entity->comp_stat;

    if (stat->health <= 0.) {
        if (stat->do_respawn) {
            stat->health = stat->max_health;
            entity->comp_position.position = entity->comp_position.spawn;
            window->cam.is_moving = true;
            window->cam.destination = &entity->comp_position.position;
            return;
        }
        if ((entity->mask & COMP_RENDER) == COMP_RENDER) {
            entity->mask = COMP_NONE;
            sfSprite_destroy(entity->comp_render.sprite);
        }
        return;
    }
    stat->health += stat->health_regen;
    if (stat->health > stat->max_health)
        stat->health = stat->max_health;
    stat->clock -= (stat->clock > 0) ? 1 : 0;
}

void sys_stat(win_t *window, world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_STAT) == COMP_STAT)
            next_frame(window, &world->entity[i], world);
}
