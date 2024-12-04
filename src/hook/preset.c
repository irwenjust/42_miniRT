#include "miniRT.h"

void camera_preset(int preset)
{
    char **new_camera;

    new_camera = NULL;
    if (preset == 1)
        new_camera = ft_split(CP_1, ' ');
    else if (preset == 2)
        new_camera = ft_split(CP_2, ' ');
    else if (preset == 3)
        new_camera = ft_split(CP_3, ' ');
    else if (preset == 4)
        new_camera = ft_split(CP_4, ' ');
    else if (preset == 5)
        new_camera = ft_split(CP_5, ' ');
    else if (preset == 6)
        new_camera = ft_split(CP_6, ' ');
    if (!new_camera)
        ft_putstr_fd("Cannot get camera preset\n", 2);
    if (!parse_camera(new_camera, &s()->camera))
        ft_putstr_fd("Cannot switch preset\n", 2);
}

void light_preset(int preset)
{
    t_light *light;

    light = s()->light->array[s()->select];
    if (preset == 1)
        light->color = RED;
    else if (preset == 2)
        light->color = YELLOW;
    else if (preset == 3)
        light->color = GREEN;
    else if (preset == 4)
        light->color = BLUE;
    else if (preset == 5)
        light->color = PINK;
    else if (preset == 6)
        light->color = PURPLE;
}

void shape_preset(int preset, int type)
{
    t_color *color;

    color = get_color(type);
    if (color == NULL)
        return ;
    if (preset == 1)
        (*color) = RED;
    else if (preset == 2)
        (*color) = YELLOW;
    else if (preset == 3)
        (*color) = GREEN;
    else if (preset == 4)
        (*color) = BLUE;
    else if (preset == 5)
        (*color) = PINK;
    else if (preset == 6)
        (*color) = PURPLE;
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
        shape_preset(preset, s()->menu);
    else if (s()->menu == VIEW)
        view_preset(preset);
    
}