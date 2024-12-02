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

void switch_preset(int preset)
{
    if (preset > 0)
        printf("switch preset\n");
    if (s()->menu == CAMERA)
        camera_preset(preset);
}