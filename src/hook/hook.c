#include "miniRT.h"

int press_key(int keycode, t_key *keys)
{
    if (keys->is_pressed == 1)
        return (0);
    keys->is_pressed = 1;
    keys->cur_keycode = keycode;
    if (keycode >= 0 && keycode < 256)
        keys->key[keycode] = 1;
    if (keycode == ESC)
        return (keys->action = QUIT, 0);
    else if (keycode == TAB || keycode == P)
        keys->action = SELECT;
    else if (keycode == G || keycode == R)
        keys->action = RESET;
    else if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
        keys->action = SCALING;
    else if (keycode == C_INC || keycode == C_DEC)
        keys->action = COLOR;
    else if (ft_strchr(MENU_KEY, (char)(keycode)))
        keys->action = MENU;
    else if (ft_strchr(PRESET_KEY, (char)(keycode)))
        keys->action = PRESET;
    else if (ft_strchr(MOVE_KEY, (char)(keycode)))
        keys->action = MOVEMENT;
    else if (ft_strchr(ROTATE_KEY, (char)(keycode)))
        keys->action = ROTATION;
    return (0);
}

/**/
int release_key(int keycode, t_key *keys)
{
    if (keys->cur_keycode == keycode)
    {
        if (keycode >= 0 && keycode < 256)
        {
            keys->key[keycode] = 0; 
        }
        keys->is_pressed = 0;
        keys->cur_keycode = -1;
        keys->action = NOTHING;
    }
    return (0);
}

//may change to void
int	ft_quit()
{
	delete_scene();
	exit(SUCCESS);
}

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
    else if (keys->action == COLOR)
        update_color(keys);
    return (0);
}
