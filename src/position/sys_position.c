/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Sys position
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "temp.h"
#include "camera.h"
#include "player.h"
#include "dialogs.h"
#include "stat.h"
#include "rendering.h"

void add_vector(entity_t *entity, sfVector2f vector, size_t lenght)
{
    for (int i = 0; i < MAX_VECTOR; ++i)
        if (entity->comp_position.vector_lenght[i] == 0) {
            entity->comp_position.velocity[i] = vector;
            entity->comp_position.vector_lenght[i] = lenght;
            return;
        }
}

static sfBool do_rect_collide(sfFloatRect rect, sfFloatRect bis)
{
    if ((rect.left < bis.left && rect.left + rect.width < bis.left)
        || (rect.left > bis.left + bis.width &&
        rect.left + rect.width > bis.left + bis.width))
        return sfFalse;
    if ((rect.top < bis.top && rect.top + rect.height < bis.top)
        || (rect.top > bis.top + bis.height &&
        rect.top + rect.height > bis.top + bis.height))
        return sfFalse;
    return sfTrue;
}

sfBool collide_entity(entity_t *entity, entity_t *bis, sfVector2f velocity)
{
    sfFloatRect entity_hitbox = entity->comp_hitbox.hitbox;
    sfFloatRect bis_hitbox = bis->comp_hitbox.hitbox;

    if (((bis->mask & (COMP_POSITION | COMP_HITBOX))
    != (COMP_POSITION | COMP_HITBOX)))
        return sfFalse;
    if (entity->comp_position.world != bis->comp_position.world)
        return sfFalse;
    entity_hitbox.left += entity->comp_position.position.x;
    entity_hitbox.left += velocity.x;
    entity_hitbox.top += entity->comp_position.position.y;
    entity_hitbox.top += velocity.y;
    bis_hitbox.left += bis->comp_position.position.x;
    bis_hitbox.top += bis->comp_position.position.y;
    if (do_rect_collide(entity_hitbox, bis_hitbox))
        return sfTrue;
    return sfFalse;
}

static void change_world(world_t *world, entity_t *entity, entity_t *portal)
{
    sfMusic_stop(world->map_list[world->map_id]->music);
    world->map_id = portal->comp_portal.dest_id;
    entity->comp_position.position =
    portal->comp_portal.dest_pos;
    entity->comp_position.world = world->map_id;
    sfMusic_play(world->map_list[world->map_id]->music);
    sfSound_play(portal->comp_portal.comp_sound.sound.sound);
}

static sfBool check_if_portal(win_t *window, entity_t *entities[2],
    world_t *world, sfVector2f velocity)
{
    if (((entities[0]->mask & COMP_PLAYER) == COMP_PLAYER) &&
        ((entities[1]->mask & COMP_PORTAL) == COMP_PORTAL) &&
        entities[1]->comp_portal.origin_id == world->map_id) {
        if (collide_entity(entities[0], entities[1], velocity)) {
            change_world(world, entities[0], entities[1]);
            init_cam(window, world, entities[0]);
        }
        return sfFalse;
    }
    if (((entities[1]->mask & COMP_HITBOX) == COMP_HITBOX) &&
        entities[1]->comp_hitbox.do_collide && (entities[1]->comp_mob.is_alive
        || (entities[1]->mask & COMP_MOB) != COMP_MOB)
        && entities[0]->comp_position.world == world->map_id)
        return collide_entity(entities[0], entities[1], velocity);
    return sfFalse;
}

bool is_close(entity_t *entity, entity_t *bis, sfVector2f threshold)
{
    if (abs(entity->comp_position.position.x -
        bis->comp_position.position.x) <= threshold.x &&
        abs(entity->comp_position.position.y -
        bis->comp_position.position.y) <= threshold.y)
        return true;
    return false;
}

sfBool check_collision(entity_t *entity, world_t *world,
    sfVector2f velocity, win_t *window)
{
    sfFloatRect hitbox = entity->comp_hitbox.hitbox;
    sfVector2f position = entity->comp_position.position;

    if (((entity->mask & COMP_HITBOX) != COMP_HITBOX)
    || !entity->comp_hitbox.do_collide ||
    entity->comp_position.world != world->map_id)
        return sfFalse;
    if (is_colliding(world, entity, velocity))
        return sfTrue;
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if (entity->entity != i && is_in_cam_range(window, &world->entity[i])
        && check_if_portal(window, (entity_t *[2]) {entity, &world->entity[i]}
        , world, velocity)) {
            do_attack(entity, &world->entity[i]);
            do_attack(&world->entity[i], entity);
            return sfTrue;
        }
    }
    return sfFalse;
}

static void sum_vectors_x_y(entity_t *entity, sfVector2f *yvelo,
    sfVector2f *xvelo)
{
    for (int i = 0; i < MAX_VECTOR; ++i)
        if (entity->comp_position.vector_lenght[i] > 0) {
            yvelo->y += entity->comp_position.velocity[i].y;
            xvelo->x += entity->comp_position.velocity[i].x;
            entity->comp_position.vector_lenght[i] -= 1;
        }
}

static void next_frame(entity_t *entity, world_t *world, win_t *window)
{
    sfVector2f xvelo = (sfVector2f) {0., 0.};
    sfVector2f yvelo = (sfVector2f) {0., 0.};
    map_list_t *map = world->map_list[world->map_id];

    no_input_dialogs(window, world);
    item_collision(world, entity);
    if (entity->comp_position.can_move == false ||
    ((entity->mask & COMP_MOB) == COMP_MOB) && !entity->comp_mob.is_alive)
        return;
    sum_vectors_x_y(entity, &yvelo, &xvelo);
    if (xvelo.x != 0. && !check_collision(entity, world, xvelo, window)) {
            if ((entity->mask & COMP_PLAYER) == COMP_PLAYER)
                update_cam(window, entity, map, xvelo);
            entity->comp_position.position.x += xvelo.x;
        }
    if (yvelo.y != 0. && !check_collision(entity, world, yvelo, window)) {
        if ((entity->mask & COMP_PLAYER) == COMP_PLAYER)
                update_cam(window, entity, map, yvelo);
            entity->comp_position.position.y += yvelo.y;
    }
}

void sys_position(world_t *world, win_t *window)
{
    if (window->cam.is_moving)
        return;
    for (size_t i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_POSITION) == COMP_POSITION
        && is_in_cam_range(window, &world->entity[i]))
            next_frame(&world->entity[i], world, window);
}
