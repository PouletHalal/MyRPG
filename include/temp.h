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

    #define ENTITY_COUNT 10000

enum comp_list {
    COMP_NONE = 0,
    COMP_RENDER = 1 << 0,
    COMP_POSITION = 1 << 1,
    COMP_INPUT = 1 << 2,
    COMP_PLAYER = 1 << 3,
};

enum anim_list {
    ANIM_PROTA_IDLE,
    ANIM_PROTA_RUN,
    ANIM_PROTA_JUMP,
    ANIM_PROTA_ATTACK,
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
    {ANIM_PROTA_IDLE, "effect/prota.png", {0, 0, 32, 32}, 2, {32, 32}, {5., 5.}, 25},
    {ANIM_PROTA_RUN, "effect/prota.png", {0, 96, 32, 32}, 8, {32, 32}, {5., 5.}, 5},
    {ANIM_PROTA_JUMP, "effect/prota.png", {0, 160, 32, 32}, 8, {32, 32}, {5., 5.}, 5},
    {ANIM_PROTA_ATTACK, "effect/prota.png", {0, 256, 32, 32}, 8, {32, 32}, {5., 5.}, 5},
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

typedef struct entity_s {
    int mask;
    comp_render_t comp_render;
    comp_position_t comp_position;
    comp_input_t comp_input;
} entity_t;

typedef struct world_s {
    sfTexture *texture_list[ANIM_END];
    entity_t entity[ENTITY_COUNT];
    sfBool key_pressed[120];
} world_t;

typedef struct window_s {
    sfVideoMode mode;
    sfRenderWindow *window;
    sfEvent event;
    sfVector2f windows_scale;
} win_t;

void sys_input_and_event(world_t *world, win_t *window);
void sys_position(world_t *world);
void sys_player(world_t *world);
void sys_render(world_t *world);

sfBool is_key_pressed(entity_t *entity, sfKeyCode code);
void create_perso_style_insane(entity_t *entity, world_t *world);

void play_animation(entity_t *entity, int animation_index, sfBool does_loop);
void update_sprite_direction(entity_t *entity);
bool is_in_animation(entity_t *entity);

#endif
