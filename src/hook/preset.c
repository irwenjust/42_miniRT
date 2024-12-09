#include "miniRT.h"

// void camera_preset(int preset)
// {
//     char **new_camera;

//     new_camera = NULL;
//     if (preset == 1)
//         new_camera = ft_split(CP_1, ' ');
//     else if (preset == 2)
//         new_camera = ft_split(CP_2, ' ');
//     else if (preset == 3)
//         new_camera = ft_split(CP_3, ' ');
//     else if (preset == 4)
//         new_camera = ft_split(CP_4, ' ');
//     else if (preset == 5)
//         new_camera = ft_split(CP_5, ' ');
//     else if (preset == 6)
//         new_camera = ft_split(CP_6, ' ');
//     if (!new_camera)
//         ft_putstr_fd("Cannot get camera preset\n", 2);
//     if (!parse_camera(new_camera, &s()->camera))
//         ft_putstr_fd("Cannot switch preset\n", 2);
// }

t_vector camera_position(t_vector min, t_vector max, int preset)
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
        new_camera.normal = (t_vector){0, 0, 1};
    else if (preset == 2)
        new_camera.normal = (t_vector){0, 0, -1};
    else if (preset == 3)
        new_camera.normal = (t_vector){0, -1, 0};
    else if (preset == 4)
        new_camera.normal = (t_vector){0, 1, 0};
    else if (preset == 5)
        new_camera.normal = (t_vector){1, 0, 0};
    else if (preset == 6)
        new_camera.normal = (t_vector){-1, 0, 0};
    s()->camera = copy_camera(new_camera);
    
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

// void shape_preset(int preset)
// {
//     t_color *color;

//     color = get_color(SHAPE);
//     if (color == NULL)
//         return ;
//     if (preset == 1)
//         (*color) = RED;
//     else if (preset == 2)
//         (*color) = YELLOW;
//     else if (preset == 3)
//         (*color) = GREEN;
//     else if (preset == 4)
//         (*color) = BLUE;
//     else if (preset == 5)
//         (*color) = PINK;
//     else if (preset == 6)
//         (*color) = PURPLE;
// }

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
    if (preset == 1)
    {
        camera_preset(1);
        light_preset(1);
        //shape_preset(1);
    }
}

void switch_preset(int preset)
{
    if (preset > 0)
        printf("switch preset\n");
    if (s()->menu == CAMERA)
        camera_preset(preset);
    else if (s()->menu == LIGHT)
        light_preset(preset);
    else if (s()->menu == SHAPE)
        shape_preset(preset);
    else if (s()->menu == VIEW)
        view_preset(preset);
    
}