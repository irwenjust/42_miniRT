/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_click_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:33:06 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:33:10 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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
		render(0);
	}
	keys->action = NOTHING;
}

/*FOR TEST, need to update later*/
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
		render(0);
	}
	keys->action = NOTHING;
}

void	update_reset(t_key *keys)
{
	if (keys->key[R])
		render(0);
	else if (keys->key[G])
	{
		if (s()->menu == CAMERA)
			reset_camera();
		if (s()->menu == LIGHT)
			reset_lights();
		if (s()->menu == SHAPE)
			reset_shapes();
		if (s()->menu == VIEW)
			reset_all();
		s()->preset = 0;
		rebuild_bvh();
		render(0);
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
