/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:24:37 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 11:44:27 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	delete_fclass(t_fclass *fclass)
{
	if (!fclass)
		return ;
	free_matrix((char **)fclass->array);
	free(fclass);
}

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	delete_scene(void)
{
	delete_fclass(s()->light);
	delete_fclass(s()->shapes);
	delete_fclass(s()->ori_light);
	delete_fclass(s()->ori_shapes);
	free_matrix(s()->args);
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

void	error(char *str)
{
	printf("error\n%s\n", str);
}

void	error_exit(char *message)
{
	delete_scene();
	printf("Error\n%s\n", message);
	exit(FAILURE);
}
