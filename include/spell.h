/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** spell
*/

#ifndef SPELL_H_
    #define SPELL_H_

typedef struct memory_s {
    struct entity_s *entity_seen;
    struct memory_s *next;
} memory_t;

enum target {
    NONE,
    SELF,
    ONE_ENNEMY,
    ALL_ENNEMY,
    ONE_ALLY,
    ALL_ALLY,
};

typedef struct target_names_s {
    char *name;
    enum target target;
} target_names_t;

static const target_names_t TARGET_NAMES[] =
{
    {"none", NONE},
    {"self", SELF},
    {"one_ennemy", ONE_ENNEMY},
    {"all_ennemy", ALL_ENNEMY},
    {"one_ally", ONE_ALLY},
    {"all_ally", ALL_ALLY},
    {NULL, NONE},
};

enum move_type {
    DIRECT,
    FOLLOW,
};

typedef struct move_names_s {
    char *name;
    enum move_type move_type;
} move_names_t;

static const move_names_t MOVE_NAMES[] =
{
    {"direct", DIRECT},
    {"follow", FOLLOW},
    {NULL, DIRECT},
};

enum spell {
    SPELL_DARK,
    SPELL_END
};

enum effect_type {
    HEAL,
    DAMAGE,
};

typedef struct effect_s {
    char *name;
    int effect_type;
    int value;
    int base_tick_cooldown;
    int duration;
} effect_t;

enum effect {
    NO_EFFECT,
    EFFECT_BURN,
};

typedef struct effect_names_s {
    char *name;
    enum effect effect;
} effect_names_t;

static const effect_names_t EFFECT_NAMES[] =
{
    {"no_effect", NO_EFFECT},
    {"burn", EFFECT_BURN},
    {NULL, NO_EFFECT},
};


int get_target_id(char *name);
int get_move_id(char *name);
int get_effect_id(char *name);


#endif /* !PLAYER_H_ */
