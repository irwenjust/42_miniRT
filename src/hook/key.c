#include "miniRT.h"

int press_key(int keycode, t_key *keys)
{
    if (keys->key_pressed)
        return (0);
    keys->key_pressed = 1;
    keys->cur_keycode = keycode;
    if (keycode == ESC)
    {
        keys->action = QUIT;
        return (0);
    }
    else if (keycode == TAB)
        keys->action = SELECT;
    else if (keycode >= 0 && keycode < 256)
        keys->key[keycode] = 1;
    //get key action
    if (ft_strchr(MENU_KEY, (char)(keycode)))
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
        keys->key_pressed = 0;
        keys->action = NOTHING;
        keys->cur_keycode = -1;
    }
    return (0);
}