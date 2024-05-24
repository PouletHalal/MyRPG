/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** disp_part
*/

#include <string.h>
#include "particle.h"
#include "temp.h"

static void display_particle(win_t *window, comp_particle_t *particle,
    world_t *world)
{
    sfRectangleShape *rect = particle->rectangle;

    for (int i = 0; i < particle->max_particles; ++i)
        if (particle->particles[i].lifespan > 0) {
            sfRectangleShape_setPosition(rect, particle->particles[i].pos);
            sfRectangleShape_setRotation(rect, particle->particles[i].angle);
            sfRenderWindow_drawRectangleShape(window->window, rect, NULL);
            sfRectangleShape_setRotation(rect, -particle->particles[i].angle);
        }
}

void display_particles(win_t *window, world_t *world)
{
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_PARTICLE) == COMP_PARTICLE
        && world->map_id == world->entity->comp_particle.world)
            display_particle(window, &world->entity[i].comp_particle, world);
}
