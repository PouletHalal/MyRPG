/*
** EPITECH PROJECT, 2024
** My rpg
** File description:
** Temp Header File
*/

#ifndef TEMP_H_
    #define TEMP_H_

    #include <SFML/Graphics.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include "maps.h"

    #define ENTITY_COUNT 10000
    #define NB_KEYS 120

enum map_ids {
    MAIN_WORLD,
    HOUSE1,
};

enum comp_list {
    COMP_NONE = 0,
    COMP_RENDER = 1 << 0,
    COMP_POSITION = 1 << 1,
    COMP_INPUT = 1 << 2,
    COMP_PLAYER = 1 << 3,
    COMP_MOB = 1 << 4,
    COMP_HITBOX = 1 << 5,
    COMP_PORTAL = 1 << 6,
};

enum anim_list
{
    ANIM_PROTA_IDLE,
    ANIM_PROTA_RUN,
    ANIM_PROTA_JUMP,
    ANIM_PROTA_ATTACK,
    ANIM_PROTA_DODO,
    ANIM_MOB_RUN,
    ANIM_PORTAL_GREEN,
    ANIM_END,
};

typedef struct animation_s {
    enum anim_list index;
    char *filename;
    sfIntRect base_text_rect;
    size_t frame_count;
    sfVector2i frame_size;
    sfVector2f scale;
    int frame_rate;
} animation_t;

static const animation_t animation_list[] = {
    {ANIM_PROTA_IDLE, "effect/prota.png", {0, 0, 32, 32}, 2, {32, 32}, {1., 1.}, 25},
    {ANIM_PROTA_RUN, "effect/prota.png", {0, 96, 32, 32}, 8, {32, 32}, {1., 1.}, 5},
    {ANIM_PROTA_JUMP, "effect/prota.png", {0, 160, 32, 32}, 8, {32, 32}, {1., 1.}, 5},
    {ANIM_PROTA_ATTACK, "effect/prota.png", {0, 256, 32, 32}, 8, {32, 32}, {1., 1.}, 5},
    {ANIM_PROTA_DODO, "effect/prota.png", {0, 224, 32, 32}, 8, {32, 32}, {1., 1.}, 10},
    {ANIM_MOB_RUN, "effect/FDP.png", {0, 192, 192, 192}, 6, {192, 192}, {.5, .5}, 5},
    {ANIM_PORTAL_GREEN, "effect/green_portal.png", {0, 0, 32, 32}, 6, {32, 32}, {1., 1.}, 5},
/*    {"effect/dark.png", {0, 0, 40, 32}, 10, {40, 32}, {1., 1.}, 5},
    {"effect/FDP.png", {0, 0, 192, 192}, 12, {192, 192}, {1., 1.}, 5},
    {"effect/Acid.png", {0, 0, 32, 32}, 16, {32, 32}, {1., 1.}, 5},
    {"effect/Dark2.png", {0, 0, 48, 64}, 16, {48, 64}, {1., 1.}, 5},
    {"effect/acid2.png", {0, 0, 56, 32}, 6, {56, 32}, {1., 1.}, 5},
    {"effect/effect1.png", {0, 0, 64, 32}, 6, {64, 32}, {1., 1.}, 5},
    {"effect/explo.png", {0, 0, 48, 48}, 18, {48, 48}, {1., 1.}, 5},
    {"effect/explo2.png", {0, 0, 16, 16}, 16, {16, 16}, {1., 1.}, 5},
    {"effect/holy.png", {0, 0, 48, 48}, 16, {48, 48}, {1., 1.}, 5},
    {"effect/ice.png", {0, 0, 32, 32}, 8, {32, 32}, {1., 1.}, 5},
    {"effect/Smear1.png", {0, 0, 48, 48}, 6, {48, 48}, {1., 1.}, 5},
    {"effect/Smear2.png", {0, 0, 48, 48}, 6, {48, 48}, {1., 1.}, 5},
    {"effect/Smear3.png", {0, 0, 48, 48}, 6, {48, 48}, {1., 1.}, 5},
    {"effect/thr1.png", {0, 0, 64, 32}, 6, {64, 32}, {1., 1.}, 5},
    {"effect/thr2.png", {0, 0, 64, 32}, 6, {64, 32}, {1., 1.}, 5},
    {"effect/thr3.png", {0, 0, 64, 32}, 6, {64, 32}, {1., 1.}, 5},
    {"effect/thr4.png", {0, 0, 64, 32}, 6, {64, 32}, {1., 1.}, 5},
    {"effect/prota.png", {0, 96, 32, 32}, 8, {32, 32}, {5., 5.}, 5},*/
};

typedef struct comp_render_s {
    animation_t *current_animation;
    sfSprite *sprite;
    sfTexture *texture;
    bool is_visible;
    bool does_loop;
    size_t act_frame;
    size_t clock;
} comp_render_t;

typedef struct comp_position_s {
    sfVector2f position;
    sfVector2f velocity;
} comp_position_t;

typedef struct comp_input_s {
    sfBool *key_pressed;
} comp_input_t;

typedef struct comp_portal_s {
    enum map_ids origin_id;
    enum map_ids dest_id;
    sfVector2f dest_pos;
} comp_portal_t;

typedef struct comp_mob_s {
    bool is_alive;
    bool does_follow;
    double range;
    size_t speed;
    bool does_take_damage;
} comp_mob_t;

typedef struct comp_hitbox_s {
    sfBool do_collide;
    sfFloatRect hitbox;
} comp_hitbox_t;

typedef struct entity_s {
    int mask;
    int entity;
    comp_render_t comp_render;
    comp_position_t comp_position;
    comp_input_t comp_input;
    comp_mob_t comp_mob;
    comp_hitbox_t comp_hitbox;
    comp_portal_t comp_portal;
} entity_t;

typedef struct world_s {
    enum map_ids map_id;
    	map_list_t **map_list;
    sfTexture *texture_list[ANIM_END];
    entity_t entity[ENTITY_COUNT];
    sfBool key_pressed[NB_KEYS];
} world_t;

typedef struct cam_s {
    sfFloatRect view_rect;
    sfView *view;
} cam_t;

typedef struct window_s {
    sfVideoMode mode;
    sfRenderWindow *window;
    sfEvent event;
    sfVector2f windows_scale;
    cam_t cam;
} win_t;

void sys_input_and_event(world_t *world, win_t *window);
void sys_position(world_t *world, win_t *window);
void sys_mob(world_t *world);
void sys_render(world_t *world);
void init_entity(world_t *world, enum anim_list anim_nbr, sfVector2f position);
void init_mob(world_t *world, enum anim_list anim_nbr, sfVector2f position);
sfBool is_key_pressed(entity_t *entity, sfKeyCode code);
int len_array(char **array);
void init_textures(world_t *world);
int find_empty(world_t *world);
sfBool collide_entity(entity_t *entity, entity_t *bis, sfVector2f velocity);
void read_portalconf(world_t *world);
void init_comp_portal(entity_t *entity, char **split);
void init_comp_render(entity_t *entity, world_t *world,
    enum anim_list anim_nbr, sfVector2f position);

void play_animation(entity_t *entity, int animation_index, sfBool does_loop);
void update_sprite_direction(entity_t *entity);
bool is_in_animation(entity_t *entity);

#endif /* !TEMP_H_ */
