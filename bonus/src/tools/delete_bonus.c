/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:45:50 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/18 12:22:05 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	free_shape_array(t_shape **shapes)
{
	t_shape	*shape;
	int		i;

	i = -1;
	while (shapes[++i])
	{
		shape = shapes[i];
		if (shape->cboard)
		{
			mlx_destroy_image(s()->win.mlx, shape->cboard->img_ptr);
			free(shape->cboard);
		}
		if (shape->tex)
		{
			mlx_destroy_image(s()->win.mlx, shape->tex->img_ptr);
			free(shape->tex);
		}
		if (shape->bmp)
		{
			mlx_destroy_image(s()->win.mlx, shape->bmp->img_ptr);
			free(shape->bmp);
		}
		free(shape);
	}
	free(shapes);
}

static void	delete_shape(t_fclass *f)
{
	if (!f)
		return ;
	free_shape_array((t_shape **)f->array);
	free(f);
}

static void	delete_fclass(t_fclass *fclass)
{
	if (!fclass)
		return ;
	free_matrix((char **)fclass->array);
	free(fclass);
}

static void	free_test_matrix(void **matrix)
{
	size_t	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	delete_scene(void)
{
	delete_shape(s()->shapes);
	delete_fclass(s()->light);
	delete_fclass(s()->ori_light);
	delete_fclass(s()->ori_shapes);
	free_test_matrix((void **)s()->args);
	if (s()->win.img)
		mlx_destroy_image(s()->win.mlx, s()->win.img);
	if (s()->win.menu)
		mlx_destroy_image(s()->win.mlx, s()->win.menu);
	if (s()->win.disp)
		mlx_destroy_window(s()->win.mlx, s()->win.disp);
	if (s()->win.mlx)
	{
		mlx_do_key_autorepeaton(s()->win.mlx);
		mlx_destroy_display(s()->win.mlx);
	}
	if (s()->bvh)
		free_bvh(&s()->bvh);
	ft_free(&s()->win.mlx);
}
