/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:24 by likong            #+#    #+#             */
/*   Updated: 2024/11/20 16:09:26 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_press(int keycode)
{
	if (keycode == ESC)
		ft_quit();
	//why dra_image here???
	//draw_image();
	render();
	return (keycode);
}

int	key_keep_press(int keycode)
{
	if (keycode == W || keycode == UP)
		s()->camera.coordinate.y += 5;
	else if (keycode == S || keycode == DOWN)
		s()->camera.coordinate.y -= 5;
	else if (keycode == A || keycode == LEFT)
		s()->camera.coordinate.x -= 5;
	else if (keycode == D || keycode == RIGHT)
		s()->camera.coordinate.x += 5;
	else if (keycode == Q)
		s()->camera.coordinate.z += 5;
	else if (keycode == E)
		s()->camera.coordinate.z -= 5;
	else if (keycode == I)
		s()->camera.normal = vector_rotate(s()->camera.normal, Z, ROTATE);
	else if (keycode == K)
		s()->camera.normal = vector_rotate(s()->camera.normal, Z, (-ROTATE));
	else if (keycode == J)
		s()->camera.normal = vector_rotate(s()->camera.normal, Y, -ROTATE);
	else if (keycode == L)
		s()->camera.normal = vector_rotate(s()->camera.normal, Y, ROTATE);
	else if (keycode == U)
		s()->camera.normal = vector_rotate(s()->camera.normal, X, -ROTATE);
	else if (keycode == O)
		s()->camera.normal = vector_rotate(s()->camera.normal, X, ROTATE);
	//why dra_image here???
	//draw_image();
	fake_render();
	return (keycode);
}

int	ft_quit()  //may change to void
{
	delete_scene();
	exit(SUCCESS);
}