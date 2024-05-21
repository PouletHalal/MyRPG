/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** spawn mob
*/

#include <math.h>
#include "temp.h"
#include "player.h"
#include "rendering.h"

static void check_spawn(entity_t *new, world_t *world, win_t *window)
{
    new->mask |= COMP_STAT | COMP_MOB;
    new->comp_mob.is_alive = true;
    new->comp_mob.does_rand_spawn = false;
    new->comp_stat.do_respawn = false;
    if (!check_collision(new, world, (sfVector2f) {0, 0}, window))
        return;
    sfSprite_destroy(new->comp_render.sprite);
    sfTexture_destroy(new->comp_render.texture);
    new->mask = COMP_NONE;
}

void spawn_copy(entity_t *entity, world_t *world, double angle, win_t *window)
{
    int free = find_empty(world);
    entity_t *new = NULL;
    sfVector2f vect = {cosf(angle) * 100., sinf(angle) * 100.};
    int player = find_comp(world, COMP_PLAYER);

    if (free == -1 || player == -1)
        return;
    vect.x += world->entity[player].comp_position.position.x;
    vect.y += world->entity[player].comp_position.position.y;
    new = &world->entity[free];
    init_comp_render(new, world, &world->animations[entity->comp_mob.anim_id], vect);
    init_comp_position(new, vect, entity->comp_position.world);
    init_comp_hitbox(new, vect);
    new->comp_mob = entity->comp_mob;
    new->comp_stat = entity->comp_stat;
    new->entity = free;
    return check_spawn(new, world, window);
}