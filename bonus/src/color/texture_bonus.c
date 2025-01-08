/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:13:56 by likong            #+#    #+#             */
/*   Updated: 2025/01/08 14:17:24 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void put_pixel(char *img_data, int pixel, t_color color)
{
	img_data[pixel + 0] = (unsigned char)(color.red * 255);   // Red
    img_data[pixel + 1] = (unsigned char)(color.green * 255); // Green
    img_data[pixel + 2] = (unsigned char)(color.blue * 255);  // Blue
    img_data[pixel + 3] = (unsigned char)(color.alpha * 255); // Alpha
	// char	*dst;

	// (void)pixel;
	// dst = img->data + (y * img->width + x) * (int)(img->bpp * 0.125);
	// *(unsigned int *)dst = (color.alpha << 24 | color.red << 16 | color.green << 8 | color.blue);
}

static void	init_image(t_image *img, int width, int height)
{
	if (!s()->win.mlx)
		printf("error\n");
	printf("mlx: %p\n", s()->win.mlx);
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

	inverted = color_sub(color_create(1, 1, 1), color);
	// checkerboard = ft_calloc(1, sizeof(t_image));
	checkerboard = (t_image *)malloc(sizeof(t_image));
	if (!checkerboard)
	{
		printf("hello 111\n");
		error_exit("error happend when initial checkboard image");
	}
	init_image(checkerboard, 256, 256);
	i = -1;
	// printf("height: %d, width: %d\n", checkerboard->height, checkerboard->width);
	while (++i < checkerboard->height)
	{
		j = -1;
		while (++j < checkerboard->width)
		{
			pixel = i * checkerboard->size_line + j * (checkerboard->bpp / 8);
			if ((i / 32 + j / 32) % 2 == 0)
				put_pixel(checkerboard->data, pixel, color);
			else
				put_pixel(checkerboard->data, pixel, inverted);
		}
	}
	return (checkerboard);
}

t_color	add_texture(t_hit *hit)
{
	if (hit->shape->checkerboard)
	{
		printf("here\n");
		return (uv_get_color(hit->shape->checkerboard, hit->u, hit->v));
	}
	return (hit->color);
}
