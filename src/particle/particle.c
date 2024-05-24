/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** particle
*/

#include <stdlib.h>
#include <math.h>
#include "particle.h"

static int find_empty_particle(comp_particle_t *particle)
{
    for (int i = 0; i < particle->max_particles; ++i)
        if (particle->particles[i].lifespan == 0) {
            particle->particles[i] = (particle_t) {0};
            return i;
        }
    return -1;
}

static void create_particle(comp_particle_t *parent, particle_t *particle)
{
    double angle = parent->angles[0] * M_PI / 180.;
    double speed = parent->speed[0];

    particle->pos.x = rand() % parent->spawn_rect.width
    + parent->spawn_rect.left;
    particle->pos.y = rand() % parent->spawn_rect.height
    + parent->spawn_rect.top;
    if (parent->angles[1] - parent->angles[0] > 0)
        angle = rand() % (parent->angles[1] - parent->angles[0]) * M_PI / 180.
        + parent->angles[0];
    if (parent->speed[1] - parent->speed[0] > 0)
        speed = rand() % (parent->speed[1] - parent->speed[0])
        + parent->speed[0];
    particle->speed.x = cos(angle) * speed;
    particle->speed.y = sin(angle) * speed;
    particle->lifespan = parent->lifespan;
}

static void next_frame(entity_t *entity)
{
    comp_particle_t *particle = &entity->comp_particle;
    int empty = 0;

    particle->time_active -= 1;
    if (particle->time_active == 0) {
        particle->is_active = sfFalse;
        return;
    }
    for (int i = 0; i < particle->max_particles; ++i)
        if (particle->particles[i].lifespan > 0) {
            particle->particles[i].pos.x += particle->particles[i].speed.x;
            particle->particles[i].pos.y += particle->particles[i].speed.y;
            particle->particles[i].lifespan -= 1;
        }
    for (int i = 0; i < particle->spawn_rate; ++i) {
        empty = find_empty_particle(particle);
        if (empty == -1)
            break;
        create_particle(particle, &particle->particles[empty]);
    }
}

void sys_particle(world_t *world)
{
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_PARTICLE) == COMP_PARTICLE
        && world->entity[i].comp_particle.is_active)
            next_frame(&world->entity[i]);
}
