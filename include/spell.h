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
    ONE_ENEMY,
    ALL_ENEMY,
    ONE_ALLY,
    ALL_ALLY,
};

enum move_type {
    DIRECT,
    FOLLOW,
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
    enum effect_type effect_type;
    int value;
    int base_tick_cooldown;
    int duration;
} effect_t;

enum effect {
    NO_EFFECT,
    EFFECT_BURN,
};

static const effect_t effect_list[] = {
    {0},
    {DAMAGE, 5, 10, 40},
};



#endif /* !PLAYER_H_ */
