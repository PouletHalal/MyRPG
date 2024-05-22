/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** ecs
*/

#ifndef ECS_H_
    #define ECS_H_

    #include <SFML/Graphics.h>
    #include <stdbool.h>
    #include "sounds.h"

    #define ENTITY_COUNT 10000
    #define NB_KEYS 120

    #define GET_BOOL(str) strcmp(str, "true") == 0 ? true : false

    #define MAX_DIALOGS 5
    #define MAX_VECTOR 10

static const char ANIM_CONF[] = "animations/animations.conf";

enum map_ids {
    MAIN_WORLD,
    HOUSE1,
    INTRO,
};

enum hud_list {
    HUD_NONE = 0,
    HUD_HEALTHBAR = 1,
    HUD_PLATE = 1 << 2,
    HUD_INVENTORY = 1 << 3,
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
    COMP_DIALOG = 1 << 7,
    COMP_STAT = 1 << 8,
    COMP_SOUND = 1 << 9,
    COMP_INVENTORY = 1 << 10,
    COMP_ITEM = 1 << 11,
    COMP_HUD = 1 << 12,
};

enum anim_list {
    ANIM_PROTA_IDLE,
    ANIM_PROTA_RUN,
    ANIM_PROTA_JUMP,
    ANIM_PROTA_ATTACK,
    ANIM_PROTA_DODO,
    ANIM_MOB_RUN,
    ANIM_PORTAL_GREEN,
    ANIM_BLACKSMITH,
    ANIM_TRANSPARENT,
    ANIM_INTRO,
    ANIM_BOY_IDLE,
    ANIM_BOY_TALK,
    ANIM_SMALL_BLUE_POTION,
    ANIM_MEDIUM_BLUE_POTION,
    ANIM_BIG_BLUE_POTION,
    ANIM_SMALL_GREEN_POTION,
    ANIM_SMALL_RED_POTION,
    ANIM_HEALTHBAR,
    ANIM_END,
};

typedef struct animation_s {
    enum anim_list index;
    char *filename;
    char *name;
    sfIntRect base_text_rect;
    size_t frame_count;
    sfVector2i frame_size;
    sfVector2f scale;
    int frame_rate;
} animation_t;

static const animation_t animation_list[] = {
/*     {ANIM_PROTA_IDLE, "effect/prota.png", "Prota Idle", {0, 0, 32, 32}, 2, {32, 32},
        {0.9, 0.9}, 25},
    {ANIM_PROTA_RUN, "effect/prota.png", "Prota Run", {0, 96, 32, 32}, 8, {32, 32},
        {0.9, 0.9}, 5},
    {ANIM_PROTA_JUMP, "effect/prota.png", "Prota Jump", {0, 160, 32, 32}, 8, {32, 32},
        {0.9, 0.9}, 5},
    {ANIM_PROTA_ATTACK, "effect/prota.png", "Prota Attack", {0, 256, 32, 32}, 8, {32, 32},
        {0.9, 0.9}, 5},
    {ANIM_PROTA_DODO, "effect/prota.png", "Prota Dodo", {0, 224, 32, 32}, 8, {32, 32},
        {0.9, 0.9}, 10},
    {ANIM_MOB_RUN, "effect/FDP.png", "Mob Run", {0, 192, 192, 192}, 6, {192, 192},
        {.5, .5}, 5},
    {ANIM_PORTAL_GREEN, "effect/green_portal.png", "Green Portal", {0, 0, 32, 32}, 6, {32, 32},
        {1., 1.}, 5},
    {ANIM_BLACKSMITH, "effect/blacksmith.png", "Blacksmith", {0, 0, 32, 32}, 8, {32, 32},
        {1, 1}, 15},
    {ANIM_TRANSPARENT, "effect/transparent.png", "Transparent", {0, 0, 32, 32}, 1, {32, 32},
        {1., 1.}, 5},
    {ANIM_INTRO, "effect/intro.png", "Intro", {0, 0, 1920, 1080}, 1, {1920, 1080},
        {1., 1.}, 5},
    {ANIM_BOY_IDLE, "effect/boy.png", "Boy Idle", {0, 0, 48, 48}, 6, {48, 48},
        {1., 1.}, 10},
    {ANIM_BOY_TALK, "effect/boy.png", "Boy Talk", {0, 448, 16, 16}, 6, {16, 16},
        {1., 1.}, 10},
    {ANIM_SMALL_BLUE_POTION, "effect/items/small_blue_potion.png", "Small Blue Potion",
        {0, 0, 32, 32}, 1, {32, 32}, {0.5, 0.5}, 5},
    {ANIM_MEDIUM_BLUE_POTION, "effect/items/medium_blue_potion.png", "Medium Blue Potion",
        {0, 0, 32, 32}, 1, {32, 32}, {0.5, 0.5}, 5},
        {ANIM_BIG_BLUE_POTION, "effect/items/big_blue_potion.png", "Big Blue Potion",
            {0, 0, 32, 32}, 1, {32, 32}, {0.5, 0.5}, 5},
    {ANIM_SMALL_GREEN_POTION, "effect/items/small_green_potion.png", "Small Green Potion",
        {0, 0, 32, 32}, 1, {32, 32}, {0.5, 0.5}, 5},
    {ANIM_SMALL_RED_POTION, "effect/items/small_red_potion.png", "Small Red Potion",
        {0, 0, 32, 32}, 1, {32, 32}, {0.5, 0.5}, 5},
    {ANIM_HEALTHBAR, "effect/healthbar.png", "Healthbar", {0, 0, 100, 6}, 1, {100, 6},
        {0.5, 0.5}, 5}, */
/*    {"effect/dark.png", {0, 0, 40, 32}, 10, {40, 32}, {1., 1.}, 5},
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

typedef struct comp_hud_s {
    int hud_type;
} comp_hud_t;

typedef struct comp_render_s {
    animation_t *current_animation;
    sfSprite *sprite;
    sfTexture *texture;
    sfTexture **texture_list;
    bool is_visible;
    bool does_loop;
    size_t act_frame;
    size_t clock;
} comp_render_t;

typedef struct comp_sound_s {
    sounds_t sound;
    sfClock *clock;
} comp_sound_t;

typedef struct comp_dialog_s {
    sfColor color;
    sfBool is_displayed;
    sfBool does_loop;
    sfBool freeze_player;
    sfBool is_finished;
    sfBool need_input;
    sfBool camera_focus;
    sfVector2f detection_area;
    int current_dialog;
    int nb_dialogs;
    int current_sentence;
    int current_char;
    char **text[MAX_DIALOGS];
    char *substring;
    sfText *sftext;
    sfFont *font;
    sfSprite *box;
    sfClock *clock;
} comp_dialog_t;

typedef struct comp_position_s {
    sfVector2f position;
    sfVector2f velocity[MAX_VECTOR];
    size_t vector_lenght[MAX_VECTOR];
    sfVector2f spawn;
    enum map_ids world;
    bool can_move;
} comp_position_t;

typedef struct comp_input_s {
    sfBool *key_pressed;
    sfBool *key_down;
    sfClock *clock;
    bool mouse_left_down;
    bool mouse_right_down;
    sfVector2f mouse_pos;
    void (*pressed_func[NB_KEYS])();
    void (*down_func[NB_KEYS])();
} comp_input_t;

typedef struct comp_portal_s {
    enum map_ids origin_id;
    enum map_ids dest_id;
    sfVector2f dest_pos;
    comp_sound_t comp_sound;
} comp_portal_t;



typedef struct comp_mob_s {
    bool is_alive;
    bool does_follow;
    double range;
    size_t speed;
    int anim_id;
    bool does_take_damage;
    bool does_rand_spawn;
    double spawn_rate;
    size_t mob_cap;
    size_t mob_count;
    bool is_clone;
    int clone;
} comp_mob_t;

typedef struct comp_hitbox_s {
    sfBool do_collide;
    sfFloatRect hitbox;
} comp_hitbox_t;

enum faction {
    FRIENDLY,
    NEUTRAL,
    ENEMY,
    MAX_FACTION,
};

typedef struct comp_stat_s {
    enum faction faction;
    double max_health;
    double health;
    double health_regen;
    sfBool do_damage;
    sfBool do_respawn;
    double damage;
    double defense;
    size_t clock;
    size_t invinsibility_frames;
} comp_stat_t;


#endif /* !ECS_H_ */
