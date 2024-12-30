#include "miniRT.h"

static void update_brightness(t_key *keys)
{
    t_light *light;

    if (s()->menu == LIGHT)
    {
        light = s()->light->array[0];
        if (keys->cur_keycode == UP && (light->brightness + 1e-8) < 1.0)
            light->brightness += 0.1;
        else if (keys->cur_keycode == DOWN && light->brightness > 1e-8)
            light->brightness -= 0.1;
    }
    else if (s()->menu == VIEW)
    {
        if (keys->cur_keycode == UP && (s()->ambient.brightness + 1e-8) < 1.0)
            s()->ambient.brightness += 0.1;
        else if (keys->cur_keycode == DOWN && s()->ambient.brightness > 1e-8)
            s()->ambient.brightness -= 0.1;
    }
}

void update_scaling(t_key *keys)
{
    t_shape *shape;
    
    if (s()->menu == SHAPE)
    {
        shape = s()->shapes->array[s()->select];
        if (shape->type == PLANE)
            return ;
        else if (shape->type == SPHERE)
        {
            scaling_sphere(keys, &shape->data.sphere);
            shape->box = shape->data.sphere.box;
        }
        else if (shape->type == CYLINDER)
        {
            scaling_cylinder(keys, &shape->data.cylinder);
            shape->box = shape->data.cylinder.box;
        }
    }
    else if (s()->menu == LIGHT || s()->menu == VIEW)
        update_brightness(keys);
    else if (s()->menu == CAMERA)
        update_camera_fov(keys);
    printf("%i\n", s()->camera.fov);
    rebuild_bvh();
    control_frame_rate();
}

void update_move(t_key *keys)
{
    if (s()->menu == CAMERA)
        move_camera(keys);
	else if (s()->menu == LIGHT)
		move_light(keys, s()->light->array[0]);
    else if (s()->menu == SHAPE)
        move_shape(keys, s()->shapes->array[s()->select]);
    else
        return ;
    // print_shape(s()->shapes->array[s()->select]);
    rebuild_bvh();
    control_frame_rate();
}

void update_rotate(t_key *keys)
{
    if (s()->menu == CAMERA)
        rotate_camera(keys);
    else if (s()->menu == SHAPE)
        rotate_shape(keys, s()->shapes->array[s()->select]);
    else
        return ;
    rebuild_bvh();
    control_frame_rate();
}

void update_color(t_key *keys)
{
    t_color *rgb;
    int *color_channel;

    rgb = get_color(s()->menu, s()->select);
    if (rgb == NULL || s()->menu == CAMERA)
        return ;
    if (s()->select_rgb == 0)
        color_channel = &(rgb->red);
    else if (s()->select_rgb == 1)
        color_channel = &(rgb->green);
    else if (s()->select_rgb == 2)
        color_channel = &(rgb->blue);
    else
        color_channel = NULL;
    if (keys->key[C_INC])
        (*color_channel)++;
    else if (keys->key[C_DEC])
        (*color_channel)--;
    if ((*color_channel) > 255)
        (*color_channel) = 0;
    if ((*color_channel) < 0)
        (*color_channel) = 255; 
    s()->preset = 0;
    control_frame_rate();
}

// void update_color(t_key *keys)
// {
//     t_color *rgb;

//     rgb = get_color();
//     if (rgb == NULL)
//         return ;
//     if (keys->key[C_INC])
//     {
//         if (s()->select_rgb == 0 && rgb->red < 255)
//             rgb->red++;
//         else if (s()->select_rgb == 1 && rgb->green < 255)
//             rgb->green++;
//         else if (s()->select_rgb == 2 && rgb->blue < 255)
//             rgb->blue++;
//     }
//     else if (keys->key[C_DEC])
//     {
//         if (s()->select_rgb == 0 && rgb->red > 0)
//             rgb->red--;
//         else if (s()->select_rgb == 1 && rgb->green > 0)
//             rgb->green--;
//         else if (s()->select_rgb == 2 && rgb->blue > 0)
//             rgb->blue--;
//     }        
//     control_frame_rate();
// }
