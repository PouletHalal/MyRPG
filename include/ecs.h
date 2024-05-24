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
    #include "spell.h"

    #define ENTITY_COUNT 10000
    #define NB_KEYS 120

    #define GET_BOOL(str) strcmp(str, "true") == 0 ? true : false

    #define MAX_DIALOGS 5
    #define MAX_VECTOR 10
    #define MAX_EFFECT 10

static const char ANIM_CONF[] = "animations/animations.conf";

enum map_ids {
    MAIN_WORLD,
    HOUSE1,
    INTRO,
    LIBRARY,
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
    COMP_NPC = 1 << 13,
    COMP_SPELL = 1 << 14,
    COMP_PARTICLE = 1 << 15,
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
    ANIM_SPELL_DARK,
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

typedef struct comp_hud_s {
    int hud_type;
} comp_hud_t;

typedef struct comp_npc_s {
    sfBool gives_item;
    sfBool need_key_item_to_talk;
    sfBool need_key_item_to_drop;
    sfBool exclamation_display;
    sfBool exclamation_end;
    int gives_item_dialog_id;
    int gives_item_sentence_id;
    int key_item_to_talk_id;
    int key_item_to_drop_id;
    int item_id;
    int exclamation_id;
} comp_npc_t;

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

typedef struct particle_s {
    sfVector2f pos;
    sfVector2f speed;
    size_t lifespan;
    double angle;
} particle_t;

enum PARTICLE_CONDITION {
    PART_NONE = 0,
    PART_MOVE = 1 << 0,
    PART_RAIN = 1 << 1,
};

typedef struct comp_particle_s {
    int condition_mask;
    sfRectangleShape *rectangle;
    sfIntRect spawn_rect;
    sfVector2f size;
    double speed[2];
    int angles[2];
    size_t max_particles;
    sfColor color;
    size_t lifespan;
    size_t spawn_rate;
    particle_t *particles;
    sfBool is_entity_centered;
    int entity;
    int world;
} comp_particle_t;

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
    sfBool level_up;
    double exp_loot;
    double exp;
    size_t level;
    double exp_requiered;
    size_t clock;
    size_t invinsibility_frames;
    effect_t *effect[MAX_EFFECT];
    int effect_duration[MAX_EFFECT];
    int effect_tick_cooldown[MAX_EFFECT];
} comp_stat_t;

typedef struct comp_spell_s {
    enum anim_list index;
    enum target target;
    enum move_type move_type;
    float damage;
    float duration;
    float speed;
    enum effect effect_index;
    animation_t *animation;
    memory_t *memory;
} comp_spell_t;

static const comp_spell_t spell_list[] = {
    {20, ALL_ENEMY, DIRECT, 5, 80, 8, EFFECT_BURN, NULL, NULL},
};

#endif /* !ECS_H_ */
