/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** window_rendering
*/

#include <stdlib.h>
#include "temp.h"
#include "maps.h"
#include "player.h"
#include "rendering.h"
#include "camera.h"
#include "dialogs.h"
#include "hud.h"


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

static void change_weather(world_t *world)
{
    if (rand() % 100000 / 1000. < WEATHER_RATE)
        world->weather = rand() % MAX_WEATHER;
}

void refresh_world(world_t *world, sfClock *clock,
    win_t *window)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    if (sfClock_getElapsedTime(clock).microseconds / 1e6 < 1. / 60.)
        return;
    sfClock_restart(clock);
    change_weather(world);
    sys_input_and_event(world, window);
    sys_player(window, world, player);
    sys_npc(window, world, player);
    sys_mob(world, window);
    sys_particle(world);
    sys_position(world, window);
    sys_spell(world);
    sys_render(window, world);
    sys_stat(window, world);
}

static bool is_renderable(entity_t *entity, int map_id)
{
    if ((entity->mask & COMP_RENDER) == COMP_RENDER &&
        entity->comp_render.is_visible == true &&
        entity->comp_position.world == map_id &&
        (entity->mask & COMP_HUD) != COMP_HUD)
        return true;
    return false;
}

static void hud_rendering(win_t *window, world_t *world, entity_t *player)
{
    sfRenderWindow_setView(window->window,
    sfRenderWindow_getDefaultView(window->window));
    display_dialogs(window, world);
    display_inventory(window, world);
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_RENDER) == COMP_RENDER &&
            world->entity[i].comp_render.is_visible == true &&
            (world->entity[i].mask & COMP_HUD) == COMP_HUD) {
                update_hud(world, player);
                sfRenderWindow_drawSprite(window->window,
                world->entity[i].comp_render.sprite, NULL);
            }
    sfRenderWindow_setView(window->window, window->cam.view);
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
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if (is_renderable(&world->entity[i], world->map_id)) {
            sfRenderWindow_drawSprite(window->window,
            world->entity[i].comp_render.sprite, NULL);
        }
    display_particles(window, world);
    display_map(window, world->map_list[world->map_id], 2);
    hud_rendering(window, world, player);
    sfRenderWindow_display(window->window);
}
