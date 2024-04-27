/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** window_rendering
*/

#include "temp.h"
#include "maps.h"
#include "player.h"
#include "rendering.h"

void draw_hitbox(win_t *window, entity_t *entity)
{
    sfFloatRect bound = sfSprite_getGlobalBounds(entity->comp_render.sprite);
    sfVector2f origin = sfSprite_getOrigin(entity->comp_render.sprite);
    sfRectangleShape *hitbox = sfRectangleShape_create();

    sfRectangleShape_setSize(hitbox, (sfVector2f) {bound.width, bound.height});
    sfRectangleShape_setOrigin(hitbox, origin);
    sfRectangleShape_setPosition(hitbox, entity->comp_position.position);
    sfRectangleShape_setFillColor(hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(hitbox, sfBlack);
    sfRectangleShape_setOutlineThickness(hitbox, 1);
    sfRenderWindow_drawRectangleShape(window->window, hitbox, NULL);
    sfRectangleShape_destroy(hitbox);
}

void refresh_world(world_t *world, sfClock *clock,
    win_t *window, map_list_t *map_list)
{
    if (sfClock_getElapsedTime(clock).microseconds / 1e6 < 1. / 60.)
        return;
    sfClock_restart(clock);
    sys_input_and_event(world, window);
    sys_mob(world);
    sys_position(world);
    sys_player(window, world, map_list);
    sys_render(world);
}

void render_window(win_t *window, world_t *world, map_list_t *map_list)
{
    sfRenderWindow_clear(window->window, sfBlack);
    display_map(window, map_list, 1);
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if ((world->entity[i].mask & COMP_RENDER) == COMP_RENDER &&
            world->entity[i].comp_render.is_visible == true)
            sfRenderWindow_drawSprite(window->window,
            world->entity[i].comp_render.sprite, NULL);
        if ((world->entity[i].mask & COMP_PLAYER) == COMP_PLAYER)
            draw_hitbox(window, &world->entity[i]);
    }
    display_map(window, map_list, 2);
    sfRenderWindow_display(window->window);
}
