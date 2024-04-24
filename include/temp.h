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

enum texture_list {
    TXT_DARK,
    TXT_FDP,
    TXT_ACID,
    TXT_DARK2,
    TXT_ACID2,
    TXT_EFFECT1,
    TXT_EXPLO,
    TXT_EXPLO2,
    TXT_HOLY,
    TXT_ICE,
    TXT_SMEAR1,
    TXT_SMEAR2,
    TXT_SMEAR3,
    TXT_THR1,
    TXT_THR2,
    TXT_THR3,
    TXT_THR4,
    TXT_END,
};

static const char *texture_file[] = {
    "effect/dark.png",
    "effect/FDP.png",
    "effect/Acid.png",
    "effect/Dark2.png",
    "effect/acid2.png",
    "effect/effect1.png",
    "effect/explo.png",
    "effect/explo2.png",
    "effect/holy.png",
    "effect/ice.png",
    "effect/Smear1.png",
    "effect/Smear2.png",
    "effect/Smear3.png",
    "effect/thr1.png",
    "effect/thr2.png",
    "effect/thr3.png",
    "effect/thr4.png",
};

typedef struct sprite_info_s {
    sfIntRect text_rect;
    size_t frame_count;
    sfVector2i frame_size;
} sprite_info_t;

static const sprite_info_t mob_list[] = {
    {{0, 0, 40, 32}, 10, {40, 32}},
    {{0, 0, 192, 192}, 12, {192, 192}},
    {{0, 0, 32, 32}, 16, {32, 32}},
    {{0, 0, 48, 64}, 16, {48, 64}},
    {{0, 0, 56, 32}, 6, {56, 32}},
    {{0, 0, 64, 32}, 6, {64, 32}},
    {{0, 0, 48, 48}, 18, {48, 48}},
    {{0, 0, 16, 16}, 16, {16, 16}},
    {{0, 0, 48, 48}, 16, {48, 48}},
    {{0, 0, 32, 32}, 8, {32, 32}},
    {{0, 0, 48, 48}, 6, {48, 48}},
    {{0, 0, 48, 48}, 6, {48, 48}},
    {{0, 0, 48, 48}, 6, {48, 48}},
    {{0, 0, 64, 32}, 6, {64, 32}},
    {{0, 0, 64, 32}, 6, {64, 32}},
    {{0, 0, 64, 32}, 6, {64, 32}},
    {{0, 0, 64, 32}, 6, {64, 32}},
};

typedef struct comp_render_s {
    sfTexture *texture;
    sfSprite *sprite;
    bool is_visible;
    bool does_loop;
    size_t frame_count;
    size_t frame;
    size_t clock;
    size_t frame_rate;
    sfVector2i frame_size;
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
    sfTexture *texture_list[TXT_END];
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

#endif /* !TEMP_H_ */
