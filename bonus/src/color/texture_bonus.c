/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:13:56 by likong            #+#    #+#             */
/*   Updated: 2025/01/14 14:48:03 by likong           ###   ########.fr       */
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
		error_exit("cannot access mlx");
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

static void	load_image(t_image *img, char *path)
{
	if (!s()->win.mlx)
		error_exit("cannot access mlx");
	img->img_ptr = mlx_xpm_file_to_image(s()->win.mlx, path, &img->width, &img->height);
	if (!img->img_ptr)
		error_exit("cannot initial image from xpm file");
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->size_line, &img->endian);
	if (!img->data)
		error_exit("error happend when initial MLX42 image address");
	// mlx_put_image_to_window(s()->win.mlx, s()->win.disp, img->img_ptr, 0, 0);
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
	else if (hit->shape->tex)
		return (uv_get_color(hit->shape->tex, hit->u, hit->v));
	return (hit->color);
}

t_image	*parse_texture(char *arg)
{
	// int		fd;
	size_t	len;
	// char	*path;
	t_image	*tex;

	len = ft_strlen(arg);
	if (len <= 4)                                          //missed check image format (only allow png)
		error_exit("The format of texture has mistake");
	tex = (t_image *)malloc(sizeof(t_image));
	if (!tex)
		error_exit("error happend when initial checkboard image");
	load_image(tex, arg);
	// shape->tex = tex;
	return (tex);
	// path = ft_strdup(arg);
	// fd = open(path, O_RDONLY);
	// if (fd < 0)
	// {
	// 	free(path);
	// 	error_exit("cannot open the file");
	// }
	// close(fd);
}

void	check_texture(char **arg, t_shape *shape)
{
	if (shape->type == PLANE && ft_strlen(arg[6]) == 1 && arg[6][0] == '1')
		shape->cboard = create_cboard(shape->data.plane.color);
	else if (shape->type == SPHERE && ft_strlen(arg[6]) == 1 && arg[6][0] == '1')
		shape->cboard = create_cboard(shape->data.sphere.color);
	else if (shape->type == CYLINDER && ft_strlen(arg[8]) == 1 && arg[8][0] == '1')
		shape->cboard = create_cboard(shape->data.cylinder.color);
	else if (shape->type == CONE && ft_strlen(arg[8]) == 1 && arg[8][0] == '1')
		shape->cboard = create_cboard(shape->data.cone.color);
	if (shape->cboard)
		return ;
	else
	{
		if (shape->type == PLANE && arg[7])
			shape->tex = parse_texture(arg[7]);
		else if (shape->type == SPHERE && arg[7])
			shape->tex = parse_texture(arg[7]);
		else if (shape->type == CYLINDER && arg[9])
			shape->tex = parse_texture(arg[9]);
		else if (shape->type == CONE && arg[9])
			shape->tex = parse_texture(arg[9]);
	}
	// if (shape->type == PLANE)
}
