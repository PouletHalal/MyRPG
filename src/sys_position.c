/*
** EPITECH PROJECT, 2024
** My_rpg
** File description:
** Sys Render file
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "temp.h"

static void next_frame(entity_t *entity)
{
    entity->comp_position.position.x += entity->comp_position.velocity.x;
    entity->comp_position.position.y += entity->comp_position.velocity.y;
}

void sys_position(world_t *world)
{
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask & COMP_POSITION == COMP_POSITION) {
            next_frame(&world->entity[i]);
        }
}
