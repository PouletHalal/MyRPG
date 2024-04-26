/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** player_movements
*/

#include <SFML/Graphics.h>
#include <SFML/Window/Keyboard.h>
#include <stdlib.h>
#include "player.h"
#include "temp.h"
#include "maps.h"

static void update_speedx(entity_t *entity, float offset)
{
    sfVector2f scale = sfSprite_getScale(entity->comp_render.sprite);
    int new_scale_x = offset / abs(offset);

    entity->comp_render.starting_rect.top = 96;
    entity->comp_render.frame_count = 8;
    entity->comp_render.frame_rate = 60 / 5;
    entity->comp_position.velocity.x = offset;
    sfSprite_setScale(entity->comp_render.sprite,
    (sfVector2f) {abs(scale.x) * new_scale_x, scale.y});
}

static void update_speedy(entity_t *entity, float offset)
{
    entity->comp_render.starting_rect.top = 96;
    entity->comp_render.frame_count = 8;
    entity->comp_render.frame_rate = 60 / 5;
    entity->comp_position.velocity.y = offset;
}

void update_sprite_animation(entity_t *entity,
    int anim_id, int count, int framerate)
{
    entity->comp_position.velocity.x = 0;
    entity->comp_position.velocity.y = 0;
    entity->comp_render.starting_rect.top = anim_id;
    entity->comp_render.frame_count = count;
    entity->comp_render.frame_rate = 60 / framerate;
}

void update_cam(win_t *window, entity_t *entity,
    map_list_t *map_list, sfVector2f offset)
{
    sfVector2f cam_pos = sfView_getCenter(window->cam.view);
    sfVector2f player_pos = entity->comp_position.position;
    int cam_width = window->cam.view_rect.width;
    int cam_height = window->cam.view_rect.height;
    sfVector2f map_size = map_list->maps->size;

    if (offset.x < 0 && cam_pos.x - cam_width / 2 > 0 - offset.x &&
        abs(player_pos.x - cam_pos.x) < THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {offset.x, 0});
    if (offset.x > 0 && cam_pos.x + cam_width / 2 < map_size.x + offset.x &&
        abs(player_pos.x - cam_pos.x) < THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {offset.x, 0});
    if (offset.y < 0 && cam_pos.y - cam_height / 2 > 0 - offset.y &&
        abs(player_pos.y - cam_pos.y) < THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {0, offset.y});
    if (offset.y > 0 && cam_pos.y + cam_height / 2 < map_size.y + offset.y
        && abs(player_pos.y - cam_pos.y) < THRESHOLD)
        sfView_move(window->cam.view, (sfVector2f) {0, offset.y});
}

static void move_player(win_t *window, entity_t *entity, map_list_t *map_list)
{
    if (is_key_pressed(entity, sfKeyD) && !is_key_pressed(entity, sfKeyQ) &&
        !is_colliding(entity, map_list, (sfVector2f) {1.5, 0})) {
        update_speedx(entity, 1.5);
        update_cam(window, entity, map_list, (sfVector2f) {1.5, 0});
    }
    if (is_key_pressed(entity, sfKeyS) && !is_key_pressed(entity, sfKeyZ) &&
        !is_colliding(entity, map_list, (sfVector2f) {0, 1.5})) {
        update_speedy(entity, 1.5);
        update_cam(window, entity, map_list, (sfVector2f) {0, 1.5});
    }
    if (is_key_pressed(entity, sfKeyQ) && !is_key_pressed(entity, sfKeyD) &&
        !is_colliding(entity, map_list, (sfVector2f) {-1.5, 0})) {
        update_speedx(entity, -1.5);
        update_cam(window, entity, map_list, (sfVector2f) {-1.5, 0});
    }
    if (is_key_pressed(entity, sfKeyZ) && !is_key_pressed(entity, sfKeyS) &&
        !is_colliding(entity, map_list, (sfVector2f) {0, -1.5})) {
        update_speedy(entity, -1.5);
        update_cam(window, entity, map_list, (sfVector2f) {0, -1.5});
    }
}

void player_movements(win_t *window, entity_t *entity,
    map_list_t *map_list)
{
    update_sprite_animation(entity, 0, 2, 2);
    if (is_key_pressed(entity, sfKeySpace))
        update_sprite_animation(entity, 256, 8, 15);
    move_player(window, entity, map_list);
}
