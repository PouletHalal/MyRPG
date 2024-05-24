/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** init_particle
*/

#include <stdlib.h>
#include "particle.h"
#include "temp.h"

static void init_particle2(entity_t *entity)
{
    entity->comp_particle.particles = calloc(1000, sizeof(particle_t));
    entity->comp_particle.spawn_rate = 30;
    entity->comp_particle.speed[0] = 3;
    entity->comp_particle.speed[1] = 6;
    entity->comp_particle.time_active = 10000;
    entity->comp_particle.is_active = sfTrue;
    entity->comp_particle.lifespan = 50;
}

void init_particle(world_t *world)
{
    int free = find_empty(world);
    sfRectangleShape *rect = NULL;
    entity_t *entity = NULL;

    if (free == -1)
        return;
    entity = &world->entity[free];
    entity->mask = COMP_PARTICLE;
    entity->comp_particle.rectangle = sfRectangleShape_create();
    rect = entity->comp_particle.rectangle;
    sfRectangleShape_setFillColor(rect, sfBlue);
    sfRectangleShape_setSize(rect, (sfVector2f){3., 6.});
    entity->comp_particle.angles[0] = 90;
    entity->comp_particle.angles[1] = 90;
    entity->comp_particle.spawn_rect = (sfIntRect) {0, -200, 1280, 960};
    entity->comp_particle.max_particles = 1000;
    init_particle2(entity);
}
