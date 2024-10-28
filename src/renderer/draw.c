/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:46 by likong            #+#    #+#             */
/*   Updated: 2024/10/28 18:20:43 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	put_pixel(t_color c, int x, int y)
{
	char *dst;

	dst = s()->win.addr + (y * WIDTH + x) * (s()->win.bpp / 8);
	*(unsigned int *)dst = (c.alpha << 24 | c.red << 16 | c.green << 8 | c.blue);
}

void	draw_image()
{
	int	x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			put_pixel(BLACK, X, Y);
	}
	mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.img, 0, 0);
}
