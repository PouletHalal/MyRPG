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
    if ((attack->mask & defense->mask & COMP_STAT) != COMP_STAT
    || defense->comp_stat.clock > 0 || attack->comp_mob.does_rand_spawn
    || defense->comp_mob.does_rand_spawn || !attack->comp_stat.do_damage
    || attack->comp_stat.faction == defense->comp_stat.faction
    || defense->comp_stat.defense > attack->comp_stat.damage)
        return;
    defense->comp_stat.health -=
    attack->comp_stat.damage - defense->comp_stat.defense;
    defense->comp_stat.clock = defense->comp_stat.invinsibility_frames;
    if ((defense->mask & COMP_PLAYER) == COMP_PLAYER)
        play_animation(world, defense, get_anim_id(world, "prota_hurt"), 0);
    if (defense->comp_stat.health < 0. && attack->comp_stat.level_up)
        attack->comp_stat.exp += defense->comp_stat.exp_loot;
}

static void check_player_respawn(entity_t *entity, win_t *window)
{
    entity->comp_position.position = entity->comp_position.spawn;
    if ((entity->mask & COMP_PLAYER) != COMP_PLAYER)
        return;
    window->cam.is_moving = true;
    window->cam.destination = &entity->comp_position.position;
}

static void do_level_up(comp_stat_t *stat)
{
    stat->exp -= stat->exp_requiered;
    stat->exp_requiered *= 1.3;
    stat->level += 1;
    stat->max_health *= 1.1;
    stat->damage *= 1.1;
    stat->defense *= 1.1;
}

static void next_frame(win_t *window, entity_t *entity, world_t *world)
{
    comp_stat_t *stat = &entity->comp_stat;

    if (stat->health <= 0.) {
        if (stat->do_respawn) {
            stat->health = stat->max_health;
            check_player_respawn(entity, window);
            return;
        }
        kill_entity(entity, world);
        return;
    }
    stat->health += stat->health_regen;
    if (stat->health > stat->max_health)
        stat->health = stat->max_health;
    stat->clock -= (stat->clock > 0) ? 1 : 0;
    if (stat->level_up && stat->exp_requiered > 0.)
        while (stat->exp > stat->exp_requiered)
            do_level_up(stat);
}

void sys_stat(win_t *window, world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_STAT) == COMP_STAT)
            next_frame(window, &world->entity[i], world);
}
