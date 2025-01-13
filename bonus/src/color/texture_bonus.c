/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:13:56 by likong            #+#    #+#             */
/*   Updated: 2025/01/13 13:19:28 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void put_test_pixel(t_image *img, int i, int j, t_color color)
{
	int pixel;

	pixel = i * img->size_line + j * (img->bpp / 8);
	img->data[pixel + 0] = (unsigned char)(color.red);
    img->data[pixel + 1] = (unsigned char)(color.green);
    img->data[pixel + 2] = (unsigned char)(color.blue);
    img->data[pixel + 3] = (unsigned char)(color.alpha);
}

static void	init_image(t_image *img, int width, int height)
{
	if (!s()->win.mlx)
		printf("error\n");
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

// static t_image	*copy_cboard(t_image *img)
// {
// 	t_image	*res;

// 	res = ft_calloc(1, sizeof(t_image));
// 	if (!res)
// 		return (NULL);
// 	*res = *img;
// 	return (res);
// }

static t_image	*create_cboard(t_color color)
{
	t_image	*cboard;
	t_color	inverted;
	int		i;
	int		j;

	inverted = color_sub(WHITE, color);
	cboard = (t_image *)malloc(sizeof(t_image));
	if (!cboard)
		error_exit("error happend when initial checkboard image");
	init_image(cboard, 256, 256);
	i = -1;
	while (++i < cboard->height - 1)
	{
		j = -1;
		while (++j < cboard->width - 1)
		{
			if ((i / 32 + j / 32) % 2 == 0)
				put_test_pixel(cboard, i, j, color);
			else
				put_test_pixel(cboard, i, j, inverted);
		}
	}
	// s()->cboard = append_matrix(s()->cboard, cboard, (void *)copy_cboard);
	s()->cboard = cboard;
	s()->win.cboard = cboard->img_ptr;
	return (cboard);
}

t_color	add_texture(t_hit *hit)
{
	if (hit->shape->cboard)
		return (uv_get_color(hit->shape->cboard, hit->u, hit->v));
	return (hit->color);
}

void	check_texture(char **arg, t_shape *shape)
{
	if (shape->type == PLANE && ft_strlen(arg[6]) == 2 && arg[6][0] == '1')
		shape->cboard = create_cboard(shape->data.plane.color);
	else if (shape->type == SPHERE && ft_strlen(arg[6]) == 2 && arg[6][0] == '1')
		shape->cboard = create_cboard(shape->data.sphere.color);
	else if (shape->type == CYLINDER && ft_strlen(arg[8]) == 2 && arg[6][0] == '1')
		shape->cboard = create_cboard(shape->data.cylinder.color);
	else if (shape->type == CONE && ft_strlen(arg[8]) == 2 && arg[6][0] == '1')
		shape->cboard = create_cboard(shape->data.cone.color);
	// if (shape->type == PLANE)
}
