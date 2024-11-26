#include "miniRT.h"

int press_key(int keycode, t_key *keys)
{
    if (keys->is_pressed == 1)
        return (0);
    keys->cur_keycode = keycode;
    if (keycode >= 0 && keycode < 256)
        keys->key[keycode] = 1;
    if (keycode == ESC)
        return (keys->action = QUIT, 0);
    else if (keycode == TAB)
        keys->action = SELECT;
    else if (keycode == G)
        keys->action = RESET;
    else if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
        keys->action = SCALING;
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
        keys->action = NOTHING;
        keys->cur_keycode = -1;
        keys->is_pressed = 0;
    }
    return (0);
}