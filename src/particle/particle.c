/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** particle
*/

#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "temp.h"

static int find_empty_particle(comp_particle_t *particle)
{
    for (int i = 0; i < particle->max_particles; ++i)
        if (particle->particles[i].lifespan == 0) {
            particle->particles[i] = (particle_t) {0};
            return i;
        }
    return -1;
}

static void check_centered(entity_t *entity, particle_t *particle,
    world_t *world)
{
    comp_particle_t *parent = &entity->comp_particle;
    entity_t *follow = &world->entity[parent->entity];

    if (parent->is_entity_centered
    && ((follow->mask & COMP_POSITION) == COMP_POSITION)) {
        particle->pos.x += follow->comp_position.position.x;
        particle->pos.y += follow->comp_position.position.y;
    }
    return;
}

static void create_particle(entity_t *entity, particle_t *particle,
    world_t *world)
{
    comp_particle_t *parent = &entity->comp_particle;
    double angle = parent->angles[0] * M_PI / 180.;
    double speed = parent->speed[0];

    particle->pos.x = rand() % parent->spawn_rect.width
    + parent->spawn_rect.left;
    particle->pos.y = rand() % parent->spawn_rect.height
    + parent->spawn_rect.top;
    check_centered(entity, particle, world);
    if (parent->angles[1] - parent->angles[0] > 0)
        angle = (rand() % (parent->angles[1] - parent->angles[0]) +
        parent->angles[0]) * M_PI / 180.;
    if ((int)(parent->speed[1] - parent->speed[0]) * 100 > 0)
        speed = (rand() % ((int)(parent->speed[1] - parent->speed[0]) * 100))
        / 100 + parent->speed[0];
    particle->speed.x = cos(angle) * speed;
    particle->speed.y = sin(angle) * speed;
    particle->lifespan = parent->lifespan;
}

static void check_part_cond(entity_t *entity, world_t *world)
{
    comp_particle_t *parent = &entity->comp_particle;
    sfVector2f move = get_mouv_vector(&world->entity[parent->entity]);
    comp_particle_t *particle = &entity->comp_particle;
    int empty = 0;

    if (((parent->condition_mask & PART_MOVE) == PART_MOVE)
    && abs(move.x) < 1e-5 && abs(move.y) < 1e-5)
        return;
    if (((parent->condition_mask & PART_RAIN) == PART_RAIN)
    && world->weather != RAIN)
        return;
    for (int i = 0; i < particle->spawn_rate; ++i) {
        empty = find_empty_particle(particle);
        if (empty == -1)
            break;
        create_particle(entity, &particle->particles[empty], world);
    }
}

static void next_frame(entity_t *entity, world_t *world)
{
    comp_particle_t *particle = &entity->comp_particle;

    for (int i = 0; i < particle->max_particles; ++i)
        if (particle->particles[i].lifespan > 0) {
            particle->particles[i].pos.x += particle->particles[i].speed.x;
            particle->particles[i].pos.y += particle->particles[i].speed.y;
            particle->particles[i].lifespan -= 1;
        }
    check_part_cond(entity, world);
}

void sys_particle(world_t *world)
{
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_PARTICLE) == COMP_PARTICLE)
            next_frame(&world->entity[i], world);
}
