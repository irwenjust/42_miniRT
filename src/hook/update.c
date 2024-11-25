#include "miniRT.h"

//may change to void
int	ft_quit()
{
	delete_scene();
	exit(SUCCESS);
}

static void update_menu(t_key *keys)
{
    t_mode mode;

    mode = -1;
    if (keys->key[V])
		mode = VIEW;
	else if (keys->key[C])
		mode = CAMERA;
	else if (keys->key[B])
		mode = LIGHT;
	else if (keys->key[M])
		mode = SHAPE;
    //change mode
    if	(mode >= 0 && s()->menu.mode != mode)
	{
		s()->menu.mode = mode;
        s()->select = 0;
        render();
		display_menu();
        printf("update menu\n"); //for test
	}
    keys->action = NOTHING;
}

/*FOR TEST, need to update later*/
static void update_preset(t_key *keys)
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

static void update_select(t_key *keys)
{
    if (s()->menu.mode == SHAPE)
    {
        s()->select++;
        if (s()->select == s()->shapes->size)
			s()->select = 0;
		display_menu();
    }
    keys->action = NOTHING;
}

static void update_reset(t_key *keys)
{
    if (s()->menu.mode == CAMERA)
        s()->camera = copy_camera(s()->ori_camera);
    control_frame_rate();
    // print_camera(&s()->ori_camera);
    // print_camera(&s()->camera);
    keys->action = NOTHING;
}

int update(t_key *keys)
{
    if (keys->action == QUIT)
        ft_quit();
    else if (keys->action == MENU) 
        update_menu(keys);
    else if (keys->action == PRESET)
        update_preset(keys);
    else if (keys->action == MOVEMENT)
        update_move(keys);
    else if (keys->action == ROTATION)
        update_rotate(keys);
    else if (keys->action == SELECT)
        update_select(keys);
    else if (keys->action == RESET)
        update_reset(keys);
    return (0);
}