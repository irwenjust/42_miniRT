#include "miniRT.h"

void light_preset(int preset)
{
    t_light *light;

    light = s()->light->array[s()->select];
    if (preset == 1)
        light->color = WARM_W;
    else if (preset == 2)
        light->color = COLD_W;
    else if (preset == 3)
        light->color = SUNSET;
    else if (preset == 4)
        light->color = MOON;
    else if (preset == 5)
        light->color = CYERPK;
    else if (preset == 6)
        light->color = TOXIC;
    if (preset == 1 || preset == 2 || preset == 5)
        light->brightness = 1.0;
    else if (preset == 3 || preset == 6)
        light->brightness = 0.7;
    else if (preset == 4)
        light->brightness = 0.4;
}

void shape_preset(int preset)
{
    int i;
    int j;
    t_color *color;
    
    i = -1;
    j = 0;
    while (++i < s()->shapes->size)
    {
        color = get_color(s()->menu, i);
        if (preset == 1)
            (*color) = CS1_DREAM[j];
        else if (preset == 2)
            (*color) = CS2_SUNSET[j];
        else if (preset == 3)
            (*color) = CS3_FIRE[j];
        else if (preset == 4)
            (*color) = CS4_BLUES[j];
        else if (preset == 5)
            (*color) = CS5_FOREST[j];
        else if (preset == 6)
            (*color) = CS6_COFFEE[j];
        j++;
        if (j >= 4)
            j = 0;
    }
}

void view_preset(int preset)
{
    camera_preset(preset);
    light_preset(preset);
    shape_preset(preset);
}

void switch_preset(int preset)
{
    if (s()->menu == CAMERA)
        camera_preset(preset);
    else if (s()->menu == LIGHT)
        light_preset(preset);
    else if (s()->menu == SHAPE)
        shape_preset(preset);
    else if (s()->menu == VIEW)
        view_preset(preset);
}