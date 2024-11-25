#include "miniRT.h"

void update_menu(t_key *keys)
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
    if	(mode >= 0 && s()->menu.mode != mode)
	{
		s()->menu.mode = mode;
		display_menu();
        printf("update menu\n"); //for test
	}
    keys->action = NOTHING;
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

void update_move(t_key *keys)
{
    if (s()->menu.mode == CAMERA)
        move_camera(keys);
}

void update_rotate(t_key *keys)
{
    if (s()->menu.mode == CAMERA)
        rotate_camera(keys);
}

int update(t_key *keys)
{
    if (keys->action == QUIT)
        ft_quit();
    if (keys->action == MENU) 
        update_menu(keys);
    else if (keys->action == PRESET)
        update_preset(keys);
    else if (keys->action == MOVEMENT)
        update_move(keys);
    else if (keys->action == ROTATION)
        update_rotate(keys);
    // else if (keys->action == SELECT)
    //     update_select(keys);
    return (0);
}