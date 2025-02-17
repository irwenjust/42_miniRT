/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:29:29 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/17 11:39:43 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_camera	copy_camera(t_camera camera)
{
	return ((t_camera){
		.coordinate = vector_copy(camera.coordinate),
		.normal = vector_copy(camera.normal),
		.fov = camera.fov
	});
}

bool	parse_camera(char **arg, t_camera *camera)
{
	char	**coord;
	char	**normal;

	coord = ft_split(arg[1], ',');
	if (!coord)
		return (error("camera: fail to split coordinate"), false);
	camera->coordinate = parse_vector(coord);
	free_matrix(coord);
	normal = ft_split(arg[2], ',');
	if (!normal)
		return (error("camera: fail to split normal"), false);
	camera->normal = parse_vector(normal);
	if (vector_magnitude(camera->normal) < 1.0 - 1e-8)
		return (error("camera: normal vector is too small"), false);
	camera->normal = vector_add(camera->normal, s()->vec_min);
	camera->normal = vector_normalize(camera->normal);
	free_matrix(normal);
	camera->fov = ft_atoi(arg[3]);
	return (camera);
}

void	move_camera(t_key *keys)
{
	if (keys->key[D])
		s()->camera.coordinate.x += 0.3;
	else if (keys->key[A])
		s()->camera.coordinate.x -= 0.3;
	else if (keys->key[W])
		s()->camera.coordinate.y += 0.3;
	else if (keys->key[S])
		s()->camera.coordinate.y -= 0.3;
	else if (keys->key[E])
		s()->camera.coordinate.z += 0.3;
	else if (keys->key[Q])
		s()->camera.coordinate.z -= 0.3;
}

void	rotate_camera(t_key *keys)
{
	if (keys->key[I])
		(s()->camera.normal) = vector_rotate(s()->camera.normal, X, (-ROTATE));
	else if (keys->key[K])
		(s()->camera.normal) = vector_rotate(s()->camera.normal, X, ROTATE);
	else if (keys->key[J])
		(s()->camera.normal) = vector_rotate(s()->camera.normal, Y, (-ROTATE));
	else if (keys->key[L])
		(s()->camera.normal) = vector_rotate(s()->camera.normal, Y, ROTATE);
	else if (keys->key[O])
		(s()->camera.normal) = vector_rotate(s()->camera.normal, Z, (-ROTATE));
	else if (keys->key[U])
		(s()->camera.normal) = vector_rotate(s()->camera.normal, Z, ROTATE);
	init_viewport();
}

void	update_camera_fov(t_key *keys)
{
	if (keys->cur_keycode == UP && s()->camera.fov + 10 < 180)
		s()->camera.fov += 10;
	else if (keys->cur_keycode == DOWN && s()->camera.fov - 10 > 0)
		s()->camera.fov -= 10;
	init_viewport();
}
