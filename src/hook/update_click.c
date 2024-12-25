#include "miniRT.h"

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
        s()->select_rgb = 0;
        s()->preset = 0;
        render();
        printf("update menu\n"); //for test
	}
    keys->action = NOTHING;
}

/*FOR TEST, need to update later*/
void update_preset(t_key *keys)
{
    int i;
    int preset;

    i = 48;
    preset = -1;
    while (++i <= SIX)
    {
        if (keys->key[i])
        {
            preset = i - 48;
            break ;
        }
    }
    if (preset >= 0 && s()->preset != preset)
    {
        s()->preset = preset;
        switch_preset(preset);
        render();
        // control_frame_rate();
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
        if (s()->menu == CAMERA)
        {
            s()->camera = copy_camera(s()->ori_camera);
            init_viewport();
        }
        else if (s()->menu == LIGHT)
            s()->light->array[0] = copy_light(s()->ori_light->array[0]);
        else if (s()->menu == SHAPE)
            s()->shapes->array[s()->select] = copy_shape(s()->ori_shapes->array[s()->select]);
        else if (s()->menu == VIEW)
        {
            s()->ambient = copy_ambient(s()->ori_ambient);
            s()->camera = copy_camera(s()->ori_camera);
            s()->light->array[0] = copy_light(s()->ori_light->array[0]);
            s()->shapes->array[s()->select] = copy_shape(s()->ori_shapes->array[s()->select]);
            init_viewport();
        }
        s()->preset = 0;
        render();
    }
    keys->action = NOTHING;
}

void update_select(t_key *keys)
{
    if (s()->menu == CAMERA)
        return ;
    if (keys->cur_keycode == TAB && s()->menu != VIEW)
    {
        s()->select++;
        if ((s()->menu == SHAPE && s()->select >= s()->shapes->size) || (s()->menu == LIGHT && s()->select >= s()->light->size))
			s()->select = 0;
        s()->select_rgb = 0;
        if (s()->menu == SHAPE)
            s()->preset = 0;
    }
    else if (keys->key[P])
    {
        s()->select_rgb++;
        if (s()->select_rgb > 2)
            s()->select_rgb = 0;
    }
    display_menu();
    keys->action = NOTHING;
}


