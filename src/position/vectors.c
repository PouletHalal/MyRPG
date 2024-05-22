/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Vector file
*/

#include "world.h"

sfVector2f get_mouv_vector(entity_t *entity)
{
    sfVector2f sum = {0., 0.};

    for (int i = 0; i < MAX_VECTOR; ++i)
        if (entity->comp_position.vector_lenght[i] > 0) {
            sum.x += entity->comp_position.velocity[i].x;
            sum.y += entity->comp_position.velocity[i].y;
        }
    return sum;
}
