#include "miniRT.h"

//may change to void
int	ft_quit()
{
	delete_scene();
	exit(SUCCESS);
}

void update_menu(t_key *keys)
{
    t_menu new_menu;

    new_menu = -1;
    if (keys->key[V])
		new_menu = VIEW;
	else if (keys->key[C])
		new_menu = CAMERA;
	else if (keys->key[B])
		new_menu = LIGHT;
	else if (keys->key[M])
		new_menu = SHAPE;
    //change new_menu
    if	(new_menu >= 0 && s()->menu != new_menu)
	{
		s()->menu = new_menu;
        s()->select = 0;
        render();
        //display_menu();
        printf("update menu\n"); //for test
	}
    keys->action = NOTHING;
<<<<<<< HEAD
    //printf("here\n");
=======
    // printf("here\n");
>>>>>>> d607470 (build bvh 60%)
}

/*FOR TEST, need to update later*/
void update_preset(t_key *keys)
{
    int preset;

    preset = -1;
    if (keys->key[ONE])
		preset = 1;
	else if (keys->key[TWO])
		preset = 2;
	else if (keys->key[THREE])
		preset = 3;
    if (preset >= 0 && s()->preset != preset)
    {
        s()->preset = preset;
        printf("preset %i\n", s()->preset); //for test
    }
    keys->action = NOTHING;
}

void update_reset(t_key *keys)
{
    if (keys->key[R])
        render();
    else if (keys->key[G])
    {
        //if (s()->menu == VIEW)
        if (s()->menu == CAMERA)
            s()->camera = copy_camera(s()->ori_camera);
        else if (s()->menu == LIGHT)
            s()->light->array[0] = copy_light(s()->ori_light->array[0]);
        else if (s()->menu == SHAPE)
            s()->shapes->array[s()->select] = copy_shape(s()->ori_shapes->array[s()->select]);
        control_frame_rate();
    }
    // print_camera(&s()->ori_camera);
    // print_camera(&s()->camera);
    keys->action = NOTHING;
}

void update_select(t_key *keys)
{
    if (s()->menu == SHAPE)
    {
        if (keys->cur_keycode == TAB)
        {
            printf("selec %i\n", s()->select);
            s()->select++;
            if (s()->select >= s()->shapes->size)
			    s()->select = 0;
            s()->select_rgb = 0;
        }
        else if (keys->key[P])
        {
            s()->select_rgb++;
            if (s()->select_rgb > 2)
                s()->select_rgb = 0;
        }
        display_menu();
    }
    keys->action = NOTHING;
}


