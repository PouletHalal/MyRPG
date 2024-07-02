/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** light
*/

#include "temp.h"
#include "maps.h"
#include "player.h"
#include "rendering.h"
#include "camera.h"
#include "math.h"

static void light_set_pixel(sfImage *image, int size, int i, sfColor color)
{
    int x = i % size - size / 2;
    int y = i / size - size / 2;
    float dist_to_center = sqrt(x * x + y * y);
    float ratio = 1 - dist_to_center / (size / 2);
    sfColor new_color = {color.r * ratio,
        color.g * ratio, color.b * ratio, 100};

    if (dist_to_center < size / 2)
        sfImage_setPixel(image, x + size / 2, y + size / 2, new_color);
}

sfSprite *create_light(int size, sfColor color)
{
    sfSprite *light_sprite = sfSprite_create();
    sfTexture *light_texture = NULL;
    sfImage *image = sfImage_createFromColor(size, size, sfTransparent);

    for (int i = 0; i < size * size; i++)
        light_set_pixel(image, size, i, color);
    light_texture = sfTexture_createFromImage(image, NULL);
    sfSprite_setTexture(light_sprite, light_texture, sfTrue);
    sfSprite_setOrigin(light_sprite, (sfVector2f){size / 2, size / 2});
    return light_sprite;
}
