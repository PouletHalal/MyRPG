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
#include "camera.h"
#include "dialogs.h"

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
    win_t *window)
{
    if (sfClock_getElapsedTime(clock).microseconds / 1e6 < 1. / 60.)
        return;
    sfClock_restart(clock);
    sys_input_and_event(world, window);
    sys_mob(world);
    sys_position(world, window);
    sys_player(window, world);
    sys_render(world);
    sys_stat(world);
}

void render_window(win_t *window, world_t *world)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    full_screen(world, window);
    sfRenderWindow_clear(window->window, sfBlack);
    resize_cam(window, world->map_list[world->map_id]);
    move_cam(window, world->map_list[world->map_id]);
    move_to_destination(window);
    display_map(window, world->map_list[world->map_id], 1);
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if ((world->entity[i].mask & COMP_RENDER) == COMP_RENDER &&
            world->entity[i].comp_render.is_visible == true &&
            world->entity[i].comp_position.world == world->map_id) {
            sfRenderWindow_drawSprite(window->window,
            world->entity[i].comp_render.sprite, NULL);
        }
    }
    display_map(window, world->map_list[world->map_id], 2);
    display_dialogs(window, world);
    display_inventory(window, world);
    sfRenderWindow_setView(window->window, window->cam.view);
    sfRenderWindow_display(window->window);
}
