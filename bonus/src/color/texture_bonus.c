/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:13:56 by likong            #+#    #+#             */
/*   Updated: 2025/02/13 20:38:20 by likong           ###   ########.fr       */
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

static bool	init_image(t_image *img, int width, int height)
{
	if (!s()->win.mlx)
		return (ERROR("cannot access mlx"), false);
	img->img_ptr = mlx_new_image(s()->win.mlx, width, height);
	if (!img->img_ptr)
		return (ERROR("mlx_new_image failed"), false);
	img->width = width;
	img->height = height;
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->data)
	{
		mlx_destroy_image(s()->win.mlx, img->img_ptr);
		return (ERROR("error happend when initial MLX42 image address"), false);
	}
	return (true);
}

static bool	load_image(t_image *img, char *path)
{
	if (!s()->win.mlx)
		return (ERROR("sphere: fail to create new shpere"), false);
	img->img_ptr = mlx_xpm_file_to_image(s()->win.mlx, path, &img->width, &img->height);
	if (!img->img_ptr)
		return (ERROR("cannot initial image from xpm file"), false);
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->data)
	{
		mlx_destroy_image(s()->win.mlx, img->img_ptr);
		return (ERROR("error happend when initial MLX42 image address"), false);
	}
	printf("wtf\n");
	return (true);
}

static t_image	*create_cboard(t_color color, bool *status)
{
	t_image	*cboard;
	t_color	inverted;
	int		i;
	int		j;

	inverted = sub_color(WHITE, color);
	cboard = (t_image *)malloc(sizeof(t_image));
	if (!cboard)
		return (ERROR("error happend when initial checkboard image"), NULL);
	if (!init_image(cboard, 256, 256))
		ft_free(cboard);
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
	*status = true;
	return (cboard);
}

t_color	add_texture(t_hit *hit)
{
	if (hit->shape->cboard)
		return (uv_get_color(hit->shape->cboard, hit->u, hit->v));
	else if (hit->shape->tex)
		return (uv_get_color(hit->shape->tex, hit->u, hit->v));
	return (hit->color);
}

static t_image	*parse_texture(char *arg, bool *status)
{
	size_t	len;
	t_image	*tex;

	len = ft_strlen(arg);
	if (len == 1 && arg[0] == '0')
	{
		*status = true;
		return (NULL);
	}
	if (len <= 4)
	{
		*status = false;
		return (ERROR("The format of texture has mistake"), NULL);
	}
	tex = (t_image *)malloc(sizeof(t_image));
	if (!tex)
	{
		*status = false;
		return (ERROR("error happend when initial checkboard image"), NULL);
	}
	if (load_image(tex, arg))
		*status = true;
	else
	{
		ft_free(tex);
		tex = NULL;                       //?????????????????????????????????
		*status = false;
	}
	return (tex);
}

bool	check_texture(char **arg, t_shape *shape)
{
	bool	status;
	
	status = false;
	if (shape->type == PLANE && ft_strlen(arg[6]) == 1 && arg[6][0] == '1')
		shape->cboard = create_cboard(shape->data.plane.color, &status);
	else if (shape->type == SPHERE && ft_strlen(arg[6]) == 1 && arg[6][0] == '1')
		shape->cboard = create_cboard(shape->data.sphere.color, &status);
	else if (shape->type == CYLINDER && ft_strlen(arg[8]) == 1 && arg[8][0] == '1')
		shape->cboard = create_cboard(shape->data.cylinder.color, &status);
	else if (shape->type == CONE && ft_strlen(arg[8]) == 1 && arg[8][0] == '1')
		shape->cboard = create_cboard(shape->data.cone.color, &status);
	if (shape->cboard)
		return (true);
	if ((shape->type == PLANE || shape->type == SPHERE))
		shape->tex = parse_texture(arg[7], &status);
	else if ((shape->type == CYLINDER || shape->type == CONE))
		shape->tex = parse_texture(arg[9], &status);
	if (!shape->tex && status == false)
		return (status);
	if ((shape->type == PLANE || shape->type == SPHERE))
		shape->bmp = parse_texture(arg[8], &status);
	else if ((shape->type == CYLINDER || shape->type == CONE))
		shape->bmp = parse_texture(arg[10], &status);
	if (!shape->bmp && status == false)
	{
		if (shape->tex)
			mlx_destroy_image(s()->win.mlx, shape->tex->img_ptr);
		ft_free(shape->tex);
	}
	return (status);
}
