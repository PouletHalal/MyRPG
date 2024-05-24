/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** particle
*/

#ifndef PARTICLE_H_
    #define PARTICLE_H_

    #include "npcs.h"

int set_world(world_t *world, entity_t *entity, char *args);
int set_spawn(world_t *world, entity_t *entity, char *args);
int set_lifespan(world_t *world, entity_t *entity, char *args);
int set_part_speed(world_t *world, entity_t *entity, char *args);
int set_angles(world_t *world, entity_t *entity, char *args);
int set_part_color(world_t *world, entity_t *entity, char *args);
int set_max_part(world_t *world, entity_t *entity, char *args);
int set_need_center(world_t *world, entity_t *entity, char *args);
int set_need_move(world_t *world, entity_t *entity, char *args);
int set_need_rain(world_t *world, entity_t *entity, char *args);
int set_part_rate(world_t *world, entity_t *entity, char *args);
int set_size(world_t *world, entity_t *entity, char *args);

static const ptr_func_t PART_ARGS[] = {
    {"world", &set_world},
    {"spawn", &set_spawn},
    {"lifespan", &set_lifespan},
    {"speed", &set_part_speed},
    {"angles", &set_angles},
    {"color", &set_part_color},
    {"max_part", &set_max_part},
    {"player_centered", &set_need_center},
    {"need_move", &set_need_move},
    {"need_rain", &set_need_rain},
    {"spawn_rate", &set_part_rate},
    {"size", &set_size},
    {0, 0},
};

#endif /* !PARTICLE_H_ */
