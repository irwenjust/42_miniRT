/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:10:34 by yzhan             #+#    #+#             */
/*   Updated: 2024/12/31 14:11:48 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	display(int x, int y, int color, char *text)
{
	if (!text)
		error_exit("Fail in menu display");
	mlx_string_put(s()->win.mlx, s()->win.disp, x, y, color, text);
}

void	display_clear(int x, int y, int color, char *text)
{
	if (!text)
		error_exit("Fail in menu display");
	mlx_string_put(s()->win.mlx, s()->win.disp, x, y, color, text);
	free(text);
}

//font width = 6, font height ~= 10
void	display_menu(void)
{
	int	y;

	y = HEIGHT * 0.88 + 20;
	mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.menu,
		0, (HEIGHT * 0.88));
	if (s()->menu == VIEW)
		view_menu(10, y);
	else if (s()->menu == CAMERA)
		camera_menu(10, y);
	else if (s()->menu == LIGHT)
		light_menu(10, y);
	else if (s()->menu == SHAPE)
		shape_menu(10, y);
}
