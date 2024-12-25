#include "miniRT.h"

static t_vector camera_position(t_vector min, t_vector max, int preset)
{
    t_vector vec;

    ft_bzero(&vec, sizeof(t_vector));
    vec.x = (min.x + max.x) / 2;
    vec.y = (min.y + max.y) / 2;
    vec.z = (min.z + max.z) / 2;
    if (preset == 1)
        vec.z = min.z - 10;
    else if (preset == 2)
        vec.z = max.z + 10;
    else if (preset == 3)
        vec.y = max.y + 10;
    else if (preset == 4)
        vec.y = min.y - 10;
    else if (preset == 5)
        vec.x = min.x - 10;
    else if (preset == 6)
        vec.x = max.x + 10;    
    return ((t_vector){vec.x, vec.y, vec.z});
}

void camera_preset(int preset)
{
    t_camera new_camera;

    new_camera = copy_camera(s()->camera);
    new_camera.coordinate = camera_position(s()->bvh->box.min, s()->bvh->box.max, preset);
    if (preset == 1)
        new_camera.normal = vector_normalize(vector_add(C_FRONT, VEC_MIN));
    else if (preset == 2)
        new_camera.normal = vector_normalize(vector_add(C_BACK, VEC_MIN));
    else if (preset == 3)
        new_camera.normal = vector_normalize(vector_add(C_TOP, VEC_MIN));
    else if (preset == 4)
        new_camera.normal = vector_normalize(vector_add(C_BOTTOM, VEC_MIN));
    else if (preset == 5)
        new_camera.normal = vector_normalize(vector_add(C_LEFT, VEC_MIN));
    else if (preset == 6)
        new_camera.normal = vector_normalize(vector_add(C_RIGHT, VEC_MIN));
    s()->camera = copy_camera(new_camera);
    init_viewport();
}

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
    // else if (s()->menu == VIEW)
    //     view_preset(preset);
}