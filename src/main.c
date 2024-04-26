/*
** EPITECH PROJECT, 2024
** My radar
** File description:
** Start file
*/

#include <stdlib.h>
#include <time.h>
#include "temp.h"
#include "maps.h"
#include "camera.h"

static int find_empty(world_t *world)
{
    for (int i = 0; i < ENTITY_COUNT; ++i)
        if (world->entity[i].mask == COMP_NONE)
            return i;
    return -1;
}

static win_t *create_win(void)
{
    win_t *window = malloc(sizeof(win_t));
    sfVideoMode mode = {WIDTH, HEIGHT, 32};

    window->window = sfRenderWindow_create(mode, "SFML window", sfClose, NULL);
    window->windows_scale = (sfVector2f) {1, 1};
    init_view(window);
    return window;
}

static void refresh_world(world_t *world, sfClock *clock,
    win_t *window, map_list_t *map_list)
{
    if (sfClock_getElapsedTime(clock).microseconds / 1e6 < 1. / 60.)
        return;
    sfClock_restart(clock);
    sys_input_and_event(world, window);
    sys_position(world);
    sys_player(window, world, map_list);
    sys_render(world);
}

static void is_prio(win_t *window, map_t *map, int priority)
{
    if (map->priority == priority)
        sfRenderWindow_drawSprite(window->window, map->sprite.sprite, NULL);
}

static void display_map(win_t *window, map_list_t *map_list, int priority)
{
    if (map_list == NULL)
        return;
    for (int j = 0; j < map_list->nb_layer; ++j) {
        is_prio(window, &(map_list->maps[j]), priority);
    }
}

static void draw_hitbox(win_t *window, entity_t *entity)
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

static void render_window(win_t *window, world_t *world, map_list_t *map_list)
{
    sfRenderWindow_clear(window->window, sfBlack);
    display_map(window, map_list, 1);
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        if (world->entity[i].mask & COMP_RENDER == COMP_RENDER &&
            world->entity[i].comp_render.is_visible == true)
            sfRenderWindow_drawSprite(window->window,
            world->entity[i].comp_render.sprite, NULL);
        if (world->entity[i].mask & COMP_PLAYER == COMP_PLAYER)
            draw_hitbox(window, &world->entity[i]);
    }
    display_map(window, map_list, 2);
    sfRenderWindow_display(window->window);
}

static void init_textures(world_t *world)
{
    world->map_id = HOUSE1;
    for (int i = 0; i < TXT_END; ++i)
        world->texture_list[i] =
        sfTexture_createFromFile(texture_file[i], NULL);
}

int main(void)
{
    world_t world = {0};
    win_t *window = create_win();
    sfClock *clock = sfClock_create();
    int ran = 17;
    tileset_t *tileset_list = init_tilesets();
    map_list_t **map_list = init_map(MAP_FILE, tileset_list);

    srand(time(NULL));
    init_textures(&world);
    init_entity(&world.entity[0], world.texture_list[ran],
        &mob_list[ran], &world);
    init_cam(window, &world);
    while (sfRenderWindow_isOpen(window->window)) {
        refresh_world(&world, clock, window, map_list[world.map_id]);
        render_window(window, &world, map_list[world.map_id]);
    }
    sfRenderWindow_destroy(window->window);
    free(window);
    return 0;
}
