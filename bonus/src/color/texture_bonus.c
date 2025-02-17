/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:13:56 by likong            #+#    #+#             */
/*   Updated: 2025/02/14 12:05:28 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	delete_texture(t_shape *shape)
{
	if (shape->tex)
		mlx_destroy_image(s()->win.mlx, shape->tex->img_ptr);
	ft_free((void **)&shape->tex);
}

static t_image	*create_cboard(t_color color, bool *status)
{
	t_image	*cboard;
	t_color	inverted;
	int		i;
	int		j;

	inverted = sub_color(hex_to_color(WHITE), color);
	cboard = (t_image *)malloc(sizeof(t_image));
	if (!cboard)
		return (ERROR("error happend when initial checkboard image"), NULL);
	if (!init_image(cboard, 256, 256))
		ft_free((void **)&cboard);
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
		return (*status = true, NULL);
	if (len <= 4)
		return (*status = true, ERROR("The texture format has mistake"), NULL);
	tex = (t_image *)malloc(sizeof(t_image));
	if (!tex)
	{
		*status = false;
		return (ERROR("error happend when initial checkboard image"), NULL);
	}
	if (load_image(tex, arg))
		return (*status = true, tex);
	else
		return (ft_free((void **)&tex), *status = false, tex);
}

bool	check_texture(char **arg, t_shape *shape)
{
	bool	status;

	status = false;
	if (shape->type == PLANE && arg[6][0] == '1')
		shape->cboard = create_cboard(shape->data.plane.color, &status);
	else if (shape->type == SPHERE && arg[6][0] == '1')
		shape->cboard = create_cboard(shape->data.sphere.color, &status);
	else if (shape->type == CYLINDER && arg[8][0] == '1')
		shape->cboard = create_cboard(shape->data.cylinder.color, &status);
	else if (shape->type == CONE && arg[8][0] == '1')
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
		delete_texture(shape);
	return (status);
}
