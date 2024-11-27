#include "miniRT.h"


static void update_move(t_key *keys)
{
    if (s()->menu == CAMERA)
        move_camera(keys);
	else if (s()->menu == LIGHT)
		move_light(keys, s()->light->array[0]);
    else if (s()->menu == SHAPE)
        move_shape(keys, s()->shapes->array[s()->select]);
    rebuild_bvh();
}

static void update_rotate(t_key *keys)
{
    if (s()->menu == CAMERA)
        rotate_camera(keys);
    if (s()->menu == SHAPE)
        rotate_shape(keys, s()->shapes->array[s()->select]);
}

static void update_scaling(t_key *keys)
{
    t_shape *shape;
    
    if (s()->menu == SHAPE)
    {
        shape = s()->shapes->array[s()->select];
        if (shape->type == PLANE)
            return ;
        else if (shape->type == SPHERE)
            scaling_sphere(keys, &shape->data.sphere);
        else if (shape->type == CYLINDER)
            scaling_cylinder(keys, &shape->data.cylinder);
        control_frame_rate();
    }
}

//void update_color(t_key *keys)
//{
//    t_shape *shape;
//    //t_color rgb;

//    if (s()->menu == SHAPE && keys->key[P])
//    {
//        shape = s()->shapes->array[s()->select];
//        if (shape->type == SPHERE)
//            shape->data.sphere.color.red--;
//        else if (shape->type == PLANE)
//            shape->data.plane.color.red--;
//        else if (shape->type == CYLINDER)
//            shape->data.cylinder.color.red--;
//        //rgb.red++;
//        control_frame_rate();
//    }
//}

int update(t_key *keys)
{
    if (keys->action == NOTHING)
        return (0);
    else if (keys->action == QUIT)
        ft_quit();
    else if (keys->action == MENU) 
        update_menu(keys);
    else if (keys->action == PRESET)
        update_preset(keys);
    else if (keys->action == RESET)
        update_reset(keys);
    else if (keys->action == SELECT)
        update_select(keys);
    else if (keys->action == SCALING)
        update_scaling(keys);
    else if (keys->action == MOVEMENT)
        update_move(keys);
    else if (keys->action == ROTATION)
        update_rotate(keys);
    //else if (keys->action == COLOR)
    //    update_color(keys);
    return (0);
}
