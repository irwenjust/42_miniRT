/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:18:26 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 11:11:05 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

bool	init_image(t_image *img, int width, int height)
{
	if (!s()->win.mlx)
		return (error("cannot access mlx"), false);
	img->img_ptr = mlx_new_image(s()->win.mlx, width, height);
	if (!img->img_ptr)
		return (error("mlx_new_image failed"), false);
	img->width = width;
	img->height = height;
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->data)
	{
		mlx_destroy_image(s()->win.mlx, img->img_ptr);
		return (error("error happend when initial MLX42 image address"), false);
	}
	return (true);
}

bool	load_image(t_image *img, char *path)
{
	if (!s()->win.mlx)
		return (error("sphere: fail to create new shpere"), false);
	img->img_ptr = mlx_xpm_file_to_image(s()->win.mlx, path,
			&img->width, &img->height);
	if (!img->img_ptr)
		return (error("cannot initial image from xpm file"), false);
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->data)
	{
		mlx_destroy_image(s()->win.mlx, img->img_ptr);
		return (error("error happend when initial MLX42 image address"), false);
	}
	return (true);
}
