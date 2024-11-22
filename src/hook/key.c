#include "miniRT.h"

int press_key(int keycode, t_key *keys)
{
    if (keys->key_pressed)
        return (0);
    keys->key_pressed = 1;
    if (keycode == ESC)
        keys->action = QUIT;
    else if (keycode < 256)
        keys->key[keycode] = 1;
    if (ft_strchr(MENU_KEY, (char)(keycode)))
        keys->action = MENU;
    if (ft_strchr(PRESET_KEY, (char)(keycode)))
        keys->action = PRESET;
    return (0);
}


int release_key(int keycode, t_key *keys)
{
    if (keycode < 256)
    {
        keys->key[keycode] = 0; 
    }
    keys->key_pressed = 0;
    keys->action = NOTHING;
    
    return (0);
}