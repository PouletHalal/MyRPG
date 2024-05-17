/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** portals
*/

#ifndef PORTALS_H_
    #define PORTALS_H_

    #include "npcs.h"

int set_origin_id(world_t *world, entity_t *entity, char *args);
int set_origin_pos(world_t *world, entity_t *entity, char *args);
int set_destination_id(world_t *world, entity_t *entity, char *args);
int set_destination_pos(world_t *world, entity_t *entity, char *args);
int set_hitbox(world_t *world, entity_t *entity, char *args);

ptr_func_t PORTAL_FLAGS[] =
{
    {"origin_id", &set_origin_id},
    {"destination_id", &set_destination_id},
    {"origin_pos", &set_origin_pos},
    {"world_id", &set_world_id},
    {"destination_pos", set_destination_pos},
    {"hitbox", &set_hitbox},
    {"animation_id", &set_idle},
    {NULL, NULL}
};

#endif /* !PORTALS_H_ */
