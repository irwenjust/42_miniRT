/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_preset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:23:02 by yzhan             #+#    #+#             */
/*   Updated: 2024/12/31 13:26:10 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vector	camera_position(t_vector min, t_vector max, int preset)
{
	t_vector	vec;
	double		diagonal;
	double		camera_distance;

	ft_bzero(&vec, sizeof(t_vector));
	vec.x = (min.x + max.x) / 2;
	vec.y = (min.y + max.y) / 2;
	vec.z = (min.z + max.z) / 2;
	diagonal = sqrt(pow(max.x - min.x, 2) + pow(max.y - min.y, 2)
			+ pow(max.z - min.z, 2));
	camera_distance = (diagonal / 2) / tan(calculate_radius(45) / 2.0);
	camera_distance += diagonal;
	if (preset == 1)
		vec.z = min.z - camera_distance;
	else if (preset == 2)
		vec.z = max.z + camera_distance;
	else if (preset == 3)
		vec.y = max.y + camera_distance;
	else if (preset == 4)
		vec.y = min.y - camera_distance;
	else if (preset == 5)
		vec.x = min.x - camera_distance;
	else if (preset == 6)
		vec.x = max.x + camera_distance;
	return ((t_vector){vec.x, vec.y, vec.z});
}

static t_vector	get_camera_dir(int preset)
{
	if (preset == 1)
		return ((t_vector){0, 0, 1});
	else if (preset == 2)
		return ((t_vector){0, 0, -1});
	else if (preset == 3)
		return ((t_vector){0, -1, 0});
	else if (preset == 4)
		return ((t_vector){0, 1, 0});
	else if (preset == 5)
		return ((t_vector){1, 0, 0});
	else
		return ((t_vector){-1, 0, 0});
}

void	camera_preset(int preset)
{
	t_camera	new_camera;
	t_vector	dir;

	new_camera = copy_camera(s()->camera);
	new_camera.coordinate = camera_position(s()->bvh->box.min,
			s()->bvh->box.max, preset);
	dir = get_camera_dir(preset);
	if (preset == 1)
		new_camera.normal = vector_normalize(vector_add(dir, s()->vec_min));
	else if (preset == 2)
		new_camera.normal = vector_normalize(vector_add(dir, s()->vec_min));
	else if (preset == 3)
		new_camera.normal = vector_normalize(vector_add(dir, s()->vec_min));
	else if (preset == 4)
		new_camera.normal = vector_normalize(vector_add(dir, s()->vec_min));
	else if (preset == 5)
		new_camera.normal = vector_normalize(vector_add(dir, s()->vec_min));
	else if (preset == 6)
		new_camera.normal = vector_normalize(vector_add(dir, s()->vec_min));
	new_camera.fov = 45;
	s()->camera = copy_camera(new_camera);
	init_viewport();
}
