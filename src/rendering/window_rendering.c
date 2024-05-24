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
#include "ui.h"

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
    if (world->ui_id == UI_NONE) {
        sys_player(window, world, player);
        sys_npc(window, world, player);
        sys_mob(world, window);
        sys_particle(world);
        sys_position(world, window);
        sys_spell(world);
        sys_render(window, world);
        sys_stat(window, world);
    }
    sys_ui(window, world);
}

static bool is_renderable(entity_t *entity, int map_id, int ui_id)
{
    if (ui_id != UI_NONE && (entity->mask & COMP_UI) == COMP_UI &&
        entity->comp_ui.ui_mask == ui_id)
        return true;
    if ((entity->mask & COMP_UI) == COMP_UI)
        return false;
    if (ui_id != UI_NONE)
        return false;
    if ((entity->mask & COMP_RENDER) == COMP_RENDER &&
        entity->comp_render.is_visible == true &&
        entity->comp_position.world == map_id &&
        (entity->mask & COMP_HUD) != COMP_HUD)
        return true;
    return false;
}

static void inventory_render(win_t *window, world_t *world, entity_t *player)
{
    display_inventory(window, world);
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if ((world->entity[i].mask & COMP_RENDER) == COMP_RENDER &&
            world->entity[i].comp_render.is_visible == true &&
            (world->entity[i].mask & COMP_HUD) == COMP_HUD &&
            (world->entity[i].mask & COMP_UI) != COMP_UI) {
                update_hud(world, player);
                sfRenderWindow_drawSprite(window->window,
                world->entity[i].comp_render.sprite, NULL);
        }
}

static void hud_rendering(win_t *window, world_t *world, entity_t *player)
{
    entity_t *mouse = &world->entity[find_comp(world, COMP_MOUSE)];

    sfRenderWindow_setView(window->window,
    sfRenderWindow_getDefaultView(window->window));
    display_dialogs(window, world);
    if (world->map_list[world->map_id]->display_hud == true)
        inventory_render(window, world, player);
    sfRenderWindow_setView(window->window, window->cam.view);
    sfRenderWindow_drawSprite(window->window, mouse->comp_render.sprite, NULL);
}

static void render_light(win_t *window, world_t *world)
{
    sfRenderStates state = {0};
    int player_index = find_comp(world, COMP_PLAYER);

    if (world->map_id != INTRO)
        return;
    sfSprite_setPosition(world->light_sprite,
        world->entity[player_index].comp_position.position);
    state.blendMode = sfBlendAdd;
    state.transform = sfTransform_Identity;
    sfRenderWindow_drawSprite(window->window, world->light_sprite, &state);
}

void render_window(win_t *window, world_t *world)
{
    entity_t *player = &world->entity[find_comp(world, COMP_PLAYER)];

    full_screen(world, window);
    sfRenderWindow_clear(window->window, sfBlack);
    if (world->is_paused == false || world->ui_id != UI_NONE)
        return;
    resize_cam(window, world->map_list[world->map_id], world);
    move_cam(window, world->map_list[world->map_id]);
    move_to_destination(window);
    display_map(window, world->map_list[world->map_id], 1);
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if (is_renderable(&world->entity[i], world->map_id, world->ui_id)) {
            sfRenderWindow_drawSprite(window->window,
            world->entity[i].comp_render.sprite, NULL);
        }
    render_light(window, world);
    display_particles(window, world);
    display_map(window, world->map_list[world->map_id], 2);
    hud_rendering(window, world, player);
    sfRenderWindow_display(window->window);
}
