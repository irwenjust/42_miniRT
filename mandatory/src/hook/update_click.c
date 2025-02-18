/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_click.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:43:05 by yzhan             #+#    #+#             */
/*   Updated: 2024/12/31 13:52:03 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	update_menu(t_key *keys)
{
	t_menu	new_menu;

	new_menu = -1;
	if (keys->key[V])
		new_menu = VIEW;
	else if (keys->key[C])
		new_menu = CAMERA;
	else if (keys->key[B])
		new_menu = LIGHT;
	else if (keys->key[M])
		new_menu = SHAPE;
	if (new_menu >= 0 && s()->menu != new_menu)
	{
		s()->menu = new_menu;
		s()->select = 0;
		s()->select_rgb = 0;
		s()->preset = 0;
		render();
	}
	keys->action = NOTHING;
}

void	update_preset(t_key *keys)
{
	int	i;
	int	preset;

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
	if (preset > 0 && preset <= 6 && s()->preset != preset)
	{
		s()->preset = preset;
		switch_preset(preset);
		render();
	}
	keys->action = NOTHING;
}

void	update_reset(t_key *keys)
{
	int	i;

	if (keys->key[R])
		render();
	else if (keys->key[G])
	{
		if (s()->menu == CAMERA || s()->menu == VIEW)
		{
			s()->camera = copy_camera(s()->ori_camera);
			init_viewport();
		}
		if (s()->menu == LIGHT || s()->menu == VIEW)
			s()->light->array[0] = copy_light(s()->ori_light->array[0]);
		if (s()->menu == SHAPE || s()->menu == VIEW)
		{
			i = -1;
			while (++i < s()->shapes->size)
				s()->shapes->array[i] = copy_shape(s()->ori_shapes->array[i]);
		}
		if (s()->menu == VIEW)
			s()->ambient = copy_ambient(s()->ori_ambient);
		s()->preset = 0;
		render();
	}
	keys->action = NOTHING;
}

void	update_select(t_key *keys)
{
	if (s()->menu == CAMERA)
		return ;
	if (keys->cur_keycode == TAB && s()->menu != VIEW)
	{
		s()->select++;
		if ((s()->menu == SHAPE && s()->select >= s()->shapes->size)
			|| (s()->menu == LIGHT && s()->select >= s()->light->size))
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
	keys->action = NOTHING;
}
