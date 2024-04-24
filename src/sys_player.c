/*
** EPITECH PROJECT, 2024
** My_rpg
** File description:
** Sys Render file
*/

#include <SFML/Graphics.h>
#include <SFML/Window/Keyboard.h>
#include <stdlib.h>
#include "temp.h"

static void next_frame(entity_t *entity)
{
    entity->comp_position.velocity.x = 0;
    entity->comp_position.velocity.y = 0;
    if (is_key_pressed(entity, sfKeyD))
        entity->comp_position.velocity.x = 5;
    if (is_key_pressed(entity, sfKeyA))
        entity->comp_position.velocity.x = -5;
    if (is_key_pressed(entity, sfKeyS))
        entity->comp_position.velocity.y = 5;
    if (is_key_pressed(entity, sfKeyW))
        entity->comp_position.velocity.y = -5;
}

void sys_player(world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask & COMP_PLAYER == COMP_PLAYER)
            next_frame(&world->entity[i]);
}
