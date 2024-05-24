/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** kill
*/

#include <stdlib.h>
#include "lib.h"
#include "temp.h"
#include "memory.h"

static void kill_dialog(entity_t *entity, world_t *world)
{
    if ((entity->mask & COMP_DIALOG) != COMP_DIALOG)
        return;
    for (int i = 0; i < MAX_DIALOGS; ++i)
        free_array(entity->comp_dialog.text[i]);
    sfText_destroy(entity->comp_dialog.sftext);
    sfClock_destroy(entity->comp_dialog.clock);
    sfFont_destroy(entity->comp_dialog.font);
    sfSprite_destroy(entity->comp_dialog.box);
}

void kill_entity(entity_t *entity, world_t *world)
{
    if ((entity->mask & COMP_MOB == COMP_MOB) && entity->comp_mob.is_clone) {
        world->entity[entity->comp_mob.clone].comp_mob.mob_count -= 1;
        world->entity[entity->comp_mob.healthbar_id].comp_render.is_visible =
        false;
        sfSprite_destroy(world->entity[entity->comp_mob.healthbar_id].
        comp_render.sprite);
        sfTexture_destroy(world->entity[entity->comp_mob.healthbar_id].
        comp_render.texture);
        world->entity[entity->comp_mob.healthbar_id].mask = COMP_NONE;
    }
    if ((entity->mask & COMP_RENDER) == COMP_RENDER) {
        sfTexture_destroy(entity->comp_render.texture);
        sfSprite_destroy(entity->comp_render.sprite);
    }
    kill_dialog(entity, world);
    if ((entity->mask & COMP_PARTICLE) == COMP_PARTICLE)
        free(entity->comp_particle.particles);
    if ((entity->mask & COMP_SPELL) == COMP_SPELL)
        free_memory(entity->comp_spell.memory);
    entity->mask = COMP_NONE;
}

static void free_sounds(sound_list_t *list)
{
    sfClock_destroy(list->clock);
    for (int i = 0; i < list->nb_sounds; ++i)
        sfSoundBuffer_destroy(list->sounds[i].buffer);
    free(list->name);
    free(list->sounds);
}

static void free_int_array(int **array)
{
    for (int i = 0; array[i] != NULL; ++i)
        free(array[i]);
    free(array);
}

static void free_maps(map_list_t **maps)
{
    if (maps == NULL)
        return;
    for (int i = 0; maps[i] != NULL; ++i) {
        for (int j = 0; j < maps[i]->nb_layer; ++j) {
            free_int_array(maps[i]->maps[j].csv_map);
            sfRenderTexture_destroy(maps[i]->maps[j].map);
            free(maps[i]->maps[j].name);
        }
        sfMusic_destroy(maps[i]->music);
        free(maps[i]->name);
        free(maps[i]);
    }
    free(maps);
}

void kill_world(world_t *world)
{
    if (world->animations != NULL) {
        for (int i = 0; world->animations[i].filename != NULL; ++i) {
            free(world->animations[i].filename);
            free(world->animations[i].name);
        }
        free(world->animations);
    }
    if (world->effect_list != NULL) {
        for (int i = 0; world->effect_list[i].name != NULL; ++i)
            free(world->effect_list[i].name);
        free(world->effect_list);
    }
    free(world->spell_list);
    if (world->sound_list != NULL) {
        for (int i = 0; world->sound_list[i] != NULL; ++i)
            free_sounds(world->sound_list[i]);
        free(world->sound_list);
    }
    free_maps(world->map_list);
}
