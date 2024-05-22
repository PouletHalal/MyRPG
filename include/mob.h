/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** mob
*/

#ifndef MOB_H_
    #define MOB_H_

    #include "npcs.h"

int set_does_follow(world_t *world, entity_t *entity, char *args);
int set_does_respawn(world_t *world, entity_t *entity, char *args);
int set_does_damage(world_t *world, entity_t *entity, char *args);
int set_range(world_t *world, entity_t *entity, char *args);
int set_does_take_damage(world_t *world, entity_t *entity, char *args);
int set_speed(world_t *world, entity_t *entity, char *args);
int set_delay(world_t *world, entity_t *entity, char *args);
int set_damage(world_t *world, entity_t *entity, char *args);
int set_defense(world_t *world, entity_t *entity, char *args);
int set_health(world_t *world, entity_t *entity, char *args);
int set_health_regen(world_t *world, entity_t *entity, char *args);
int set_faction(world_t *world, entity_t *entity, char *args);
int set_anim(world_t *world, entity_t *entity, char *args);
int set_mob_pos(world_t *world, entity_t *entity, char *args);
int set_spawn_rate(world_t *world, entity_t *entity, char *args);
int set_does_rand(world_t *world, entity_t *entity, char *args);
void spawn_copy(entity_t *entity, world_t *world, double angle, win_t *window);
int set_mob_cap(world_t *world, entity_t *entity, char *args);
int set_exp_loot(world_t *world, entity_t *entity, char *args);

static const ptr_func_t MOB_ARGS[] = {
    {"pos", &set_mob_pos},
    {"world_id", &set_world_id},
    {"does_follow", &set_does_follow},
    {"texture", &set_anim},
    {"respawn", &set_does_respawn},
    {"does_damage", &set_does_damage},
    {"range", &set_range},
    {"take_damage", &set_does_take_damage},
    {"speed", &set_speed},
    {"attack_delay", &set_delay},
    {"damage", &set_damage},
    {"defense", &set_defense},
    {"health", &set_health},
    {"health_regen", &set_health_regen},
    {"faction", &set_faction},
    {"spawn_rate", &set_spawn_rate},
    {"rand_spawn", &set_does_rand},
    {"mob_cap", &set_mob_cap},
    {"exp_loot", &set_exp_loot},
    {NULL, NULL},
};


#endif /* !MOB_H_ */
