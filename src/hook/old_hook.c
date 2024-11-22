/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:24 by likong            #+#    #+#             */
/*   Updated: 2024/11/22 11:36:46 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_press(int keycode)
{
	if (keycode == ESC)
		ft_quit();
	if (keycode == V)
		change_menu(VIEW);
	else if (keycode == C)
		change_menu(CAMERA);
	else if (keycode == B)
		change_menu(LIGHT);
	else if (keycode == M)
		change_menu(SHAPE);
	if (s()->menu.mode == SHAPE)
	{
		if (keycode == N)
			s()->select++;
		if (s()->select == s()->shapes->size)
			s()->select = 0;
		display_menu();
	}
	// if (s()->menu.mode != VIEW)
	// {
	// 	render();
	// 	printf("render\n");
	// }
	return (keycode);
}

int	key_keep_press(int keycode)
{
	if (s()->menu.mode == VIEW)
		return (keycode);
	if (keycode == W || keycode == UP)
		s()->camera.coordinate.y += 0.3;
	else if (keycode == S || keycode == DOWN)
		s()->camera.coordinate.y -= 0.3;
	else if (keycode == A || keycode == LEFT)
		s()->camera.coordinate.x -= 0.3;
	else if (keycode == D || keycode == RIGHT)
		s()->camera.coordinate.x += 0.3;
	else if (keycode == Q)
		s()->camera.coordinate.z += 0.3;
	else if (keycode == E)
		s()->camera.coordinate.z -= 0.3;
	else if (keycode == U) //I
		s()->camera.normal = vector_rotate(s()->camera.normal, Z, ROTATE);
	else if (keycode == O) //K
		s()->camera.normal = vector_rotate(s()->camera.normal, Z, (-ROTATE));
	else if (keycode == J) //J
		s()->camera.normal = vector_rotate(s()->camera.normal, Y, -ROTATE);
	else if (keycode == L) //L
		s()->camera.normal = vector_rotate(s()->camera.normal, Y, ROTATE);
	else if (keycode == I) //U
		s()->camera.normal = vector_rotate(s()->camera.normal, X, -ROTATE);
	else if (keycode == K) //O
		s()->camera.normal = vector_rotate(s()->camera.normal, X, ROTATE);
	//why dra_image here???
	//draw_image();
	// fake_render();
	
	return (keycode);
}

int	ft_quit()  //may change to void
{
	delete_scene();
	exit(SUCCESS);
}