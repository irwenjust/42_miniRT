/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:38:02 by yzhan             #+#    #+#             */
/*   Updated: 2024/12/18 20:49:38 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool new_cylinder(char **arg, t_cylinder *cylinder)
{
	char **coord;
	char **normal;
	char **rgb;

	coord = ft_split(arg[1], ',');
	if (!coord)
		return (ERROR("cylinder: fail to split coordinate"), false);
	cylinder->center = parse_vector(coord);
	free_matrix(coord);
	normal = ft_split(arg[2], ',');
	if (!normal)
		return (ERROR("cylinder: fail to split normal"), false);
	cylinder->normal = vector_normalize(parse_vector(normal));
	free_matrix(normal);
	if (vector_magnitude(cylinder->normal) < 1e-8)
		return (ERROR("cylinder: normal vector is too small"), false);
	cylinder->radius = ft_atod(arg[3]) * 0.5;
	cylinder->height = ft_atod(arg[4]);
	rgb = ft_split(arg[5], ',');
	if (!rgb)
		return (ERROR("cylinder: fail to split color"), false);
	cylinder->color = parse_color(rgb);
	cylinder->box = box_cylinder(cylinder);
	cylinder->rebuildbox = box_cylinder;
	// printf("new cy min: (%f, %f, %f), max: (%f, %f, %f)\n",
    //        cylinder->box.min.x, cylinder->box.min.y, cylinder->box.min.z,
    //        cylinder->box.max.x, cylinder->box.max.y, cylinder->box.max.z);
	free_matrix(rgb);
	return (true);
}

bool parse_cylinder(char **arg, t_fclass *fclass)
{
	t_shape *shape;
	t_cylinder cylinder;

	if (ft_matrix_size(arg) != 6 || !check_syntax(arg, "011001"))
		return (ERROR("cylinder: wrong args format"), false);
	if (ft_atod(arg[3]) * 0.5 < 1e-8)
		return (ERROR("cylinder: wrong radius value"), false);
	if (ft_atod(arg[4]) < 1e-8)
		return (ERROR("cylinder: wrong height value"), false);
	if (!check_rgb(arg[5]))
		return (ERROR("cylinder: wrong color value"), false);
	if (!new_cylinder(arg, &cylinder))
		return (ERROR("cylinder: fail to create new shpere"), false);
	cylinder.cap_u = vector_add(cylinder.center, vector_multiple(cylinder.normal, -cylinder.height * 0.5));
	cylinder.cap_b = vector_add(cylinder.center, vector_multiple(cylinder.normal, cylinder.height * 0.5));
	shape = new_shape(&cylinder, CYLINDER, fclass->size, s()->shape_nbr[CYLINDER]);
	// shape->rebuildbox = box_cylinder;
	// printf("parse cy min: (%f, %f, %f), max: (%f, %f, %f)\n",
    //        shape->data.cylinder.box.min.x, shape->data.cylinder.box.min.y, shape->data.cylinder.box.min.z,
    //        shape->data.cylinder.box.max.x, shape->data.cylinder.box.max.y, shape->data.cylinder.box.max.z);
	
	s()->shape_nbr[CYLINDER]++;
	push_to_fclass(fclass, shape);
	//printf("Pushing shape: type = %d, id = %d\n", shape->type, shape->id);
	// t_shape *new;
	// new = fclass->array[fclass->size - 1];
	// printf("parse cy min: (%f, %f, %f), max: (%f, %f, %f)\n",
    //        new->data.cylinder.box.min.x, new->data.cylinder.box.min.y, new->data.cylinder.box.min.z,
    //        new->data.cylinder.box.max.x, new->data.cylinder.box.max.y, new->data.cylinder.box.max.z);
	
	return (true);
}



void move_cylinder(t_key *keys, t_cylinder *cylinder)
{
	if (keys->key[D])
		cylinder->center.x += 0.3;
	else if (keys->key[A])
		cylinder->center.x -= 0.3;
	if (keys->key[W])
		cylinder->center.y += 0.3;
	else if (keys->key[S])
		cylinder->center.y -= 0.3;
	else if (keys->key[E])
		cylinder->center.z += 0.3;
	else if (keys->key[Q])
		cylinder->center.z -= 0.3;
	cylinder->cap_u = vector_add(cylinder->center, vector_multiple(cylinder->normal, -cylinder->height * 0.5));
	cylinder->cap_b = vector_add(cylinder->center, vector_multiple(cylinder->normal, cylinder->height * 0.5));
	cylinder->box = cylinder->rebuildbox(cylinder);
	printf("move cylinder\n");
}

void rotate_cylinder(t_key *keys, t_cylinder *cylinder)
{
	if (keys->key[I])
		cylinder->normal = vector_rotate(cylinder->normal, X, ROTATE);
	else if (keys->key[K])
		cylinder->normal = vector_rotate(cylinder->normal, X, (-ROTATE));
	else if (keys->key[L])
		cylinder->normal = vector_rotate(cylinder->normal, Y, ROTATE);
	else if (keys->key[J])
		cylinder->normal = vector_rotate(cylinder->normal, Y, (-ROTATE));
	else if (keys->key[O])
		cylinder->normal = vector_rotate(cylinder->normal, Z, ROTATE);
	else if (keys->key[U])
		cylinder->normal = vector_rotate(cylinder->normal, Z, (-ROTATE));
	cylinder->cap_u = vector_add(cylinder->center, vector_multiple(cylinder->normal, -cylinder->height * 0.5));
	cylinder->cap_b = vector_add(cylinder->center, vector_multiple(cylinder->normal, cylinder->height * 0.5));
	cylinder->box = cylinder->rebuildbox(cylinder);
	printf("rotate cylinder\n");
}

void scaling_cylinder(t_key *keys, t_cylinder *cylinder)
{
	if (keys->cur_keycode == LEFT && cylinder->radius - 0.1 > 0)
        cylinder->radius -= 0.1;
    else if (keys->cur_keycode == RIGHT)
        cylinder->radius += 0.1;
    else if (keys->cur_keycode == UP)
        cylinder->height += 0.1;
    else if (keys->cur_keycode == DOWN && cylinder->height - 0.1 > 0)
        cylinder->height -= 0.1;
    cylinder->cap_u = vector_add(cylinder->center, vector_multiple(cylinder->normal, -cylinder->height * 0.5));
	cylinder->cap_b = vector_add(cylinder->center, vector_multiple(cylinder->normal, cylinder->height * 0.5));
	cylinder->box = cylinder->rebuildbox(cylinder);
}
