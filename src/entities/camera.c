/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:51 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 18:27:49 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_camera copy_camera(t_camera camera)
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

	if (ft_matrix_size(arg) != 4 || !check_syntax(arg, "0110"))
		return (ERROR("camera: wrong args format"), false);
	coord = ft_split(arg[1], ',');
	if (!coord)
		return (ERROR("camera: fail to split coordinate"), false);
	camera->coordinate = parse_vector(coord);
	free_matrix(coord);
	normal = ft_split(arg[2], ',');
	if (!normal)
		return (ERROR("camera: fail to split normal"), false);
	camera->normal = parse_vector(normal);
	camera->normal = vector_add(camera->normal, VEC_MIN);
	free_matrix(normal);
	if (vector_magnitude(camera->normal) < 1e-8)
		return (ERROR("camera: normal vector is too small"), false);
	camera->normal = vector_normalize(camera->normal);
	camera->fov = ft_atoi(arg[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return (ERROR("camera: normal vector's visual is out of range"), false);
	return (camera);
}

void move_camera(t_key *keys)
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
    // control_frame_rate();
	// print_camera(&s()->camera);
    // printf("move camera\n");
}

void rotate_camera(t_key *keys)
{
	if (keys->key[L])
		s()->camera.normal = vector_rotate(s()->camera.normal, X, ROTATE);
	else if (keys->key[J])
		s()->camera.normal = vector_rotate(s()->camera.normal, X, (-ROTATE));
	else if (keys->key[I])
		s()->camera.normal = vector_rotate(s()->camera.normal, Y, ROTATE);
	else if (keys->key[K])
		s()->camera.normal = vector_rotate(s()->camera.normal, Y, (-ROTATE));
	else if (keys->key[O])
		s()->camera.normal = vector_rotate(s()->camera.normal, Z, ROTATE);
	else if (keys->key[U])
		s()->camera.normal = vector_rotate(s()->camera.normal, Z, (-ROTATE));
    // control_frame_rate();
	// print_camera(&s()->camera);
	init_viewport();
    // printf("rotate camera\n");
}

void update_camera_fov(t_key *keys)
{
	if (keys->cur_keycode == UP && (s()->camera.fov + 1e-8) < 180)
        s()->camera.fov += 10;
    else if (keys->cur_keycode == DOWN && s()->camera.fov > 1e-8)
		s()->camera.fov -= 10;
	init_viewport();
}