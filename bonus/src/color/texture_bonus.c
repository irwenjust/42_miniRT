/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:13:56 by likong            #+#    #+#             */
/*   Updated: 2025/01/09 20:52:31 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void put_test_pixel(char *img_data, int pixel, t_color color)
{
	img_data[pixel + 0] = (unsigned char)(color.red * 255);
    img_data[pixel + 1] = (unsigned char)(color.green * 255);
    img_data[pixel + 2] = (unsigned char)(color.blue * 255);
    img_data[pixel + 3] = (unsigned char)(color.alpha * 255);
}

static void	init_image(t_image *img, int width, int height)
{
	if (!s()->win.mlx)
		printf("error\n");
	// printf("mlx: %p\n", s()->win.mlx);
	img->img_ptr = mlx_new_image(s()->win.mlx, width, height);
	if (!img->img_ptr)
		error_exit("mlx_new_image failed");
	img->width = width;
	img->height = height;
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->data)
		error_exit("error happend when initial MLX42 image address");
}

t_image	*create_checkerboard(t_color color)
{
	t_image	*checkerboard;
	t_color	inverted;
	int		i;
	int		j;
	int		pixel;

	inverted = color_sub(WHITE, color);
	checkerboard = (t_image *)malloc(sizeof(t_image));
	if (!checkerboard)
		error_exit("error happend when initial checkboard image");
	init_image(checkerboard, 256, 256);
	i = -1;
	while (++i < checkerboard->height - 1)
	{
		j = -1;
		while (++j < checkerboard->width - 1)
		{
			pixel = i * checkerboard->size_line + j * (checkerboard->bpp / 8);
			if ((i / 32 + j / 32) % 2 == 0)
				put_test_pixel(checkerboard->data, pixel, color);
			else
				put_test_pixel(checkerboard->data, pixel, inverted);
		}
	}
	return (checkerboard);
}

t_color	add_texture(t_hit *hit)
{
	if (hit->shape->checkerboard)
		return (uv_get_color(hit->shape->checkerboard, hit->u, hit->v));
	return (hit->color);
}
