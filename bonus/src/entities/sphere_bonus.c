

#include "miniRT_bonus.h"

static bool	new_sphere(char **arg, t_sphere *sphere)
{
	char	**tmp;

	tmp = ft_split(arg[1], ',');
	if (!tmp)
		return (ERROR("sphere: fail to split coordinate"), false);
	sphere->center = parse_vector(tmp);
	free_matrix(tmp);
	sphere->radius = ft_atod(arg[2]) * 0.5;
	if (sphere->radius < 1e-8)
		return (ERROR("sphere: wrong diameter value"), false);
	tmp = ft_split(arg[3], ',');
	if (!tmp)
		return (ERROR("sphere: fail to split color"), false);
	sphere->color = parse_color(tmp);
	sphere->normal = (t_vector){0, 1, 0};
	free_matrix(tmp);
	// sphere->box = box_sphere(sphere);
	// sphere->rebuildbox = box_sphere;
	return (true);
}

bool	parse_sphere(char **arg, t_fclass *fclass)
{
	t_shape		*shape;
	t_sphere	sphere;

	if (ft_matrix_size(arg) != 7 || !check_syntax(arg, "010100"))
		return (ERROR("sphere: wrong args format"), false);
	// if (ft_atod(arg[2]) * 0.5 < 1e-8)
	// 	return (ERROR("sphere: wrong radius value"), false);
	if (!check_rgb(arg[3]))
		return (ERROR("sphere: wrong color value"), false);
	if (!new_sphere(arg, &sphere))
		return (ERROR("sphere: fail to create new shpere"), false);
	shape = new_shape(&sphere, SPHERE, fclass->size, s()->shape_nbr[SPHERE]);
	check_texture(arg, shape);
	shape->ks = ft_atod(arg[4]);
	shape->shininess = ft_atod(arg[5]);
	if (shape->ks < 1e-8 || shape->ks > 1)
		return (ERROR("sphere: wrong ks value"), false);
	if (shape->shininess < 1 || shape->shininess > 128)
		return (ERROR("sphere: wrong shininess value"), false);
	s()->shape_nbr[SPHERE]++;
	add_uv_axis(shape, shape->data.sphere.normal);
	push_to_fclass(fclass, shape);
	return (true);
}

void	rotate_sphere(t_key *keys, t_sphere *sphere)
{
	if (keys->key[I])
		sphere->normal = vector_rotate(sphere->normal, X, ROTATE);
	else if (keys->key[K])
		sphere->normal = vector_rotate(sphere->normal, X, (-ROTATE));
	else if (keys->key[L])
		sphere->normal = vector_rotate(sphere->normal, Y, ROTATE);
	else if (keys->key[J])
		sphere->normal = vector_rotate(sphere->normal, Y, (-ROTATE));
	else if (keys->key[O])
		sphere->normal = vector_rotate(sphere->normal, Z, ROTATE);
	else if (keys->key[U])
		sphere->normal = vector_rotate(sphere->normal, Z, (-ROTATE));
}

void	move_sphere(t_key *keys, t_sphere *sphere)
{
	if (keys->key[D])
		sphere->center.x += 0.3;
	else if (keys->key[A])
		sphere->center.x -= 0.3;
	else if (keys->key[W])
		sphere->center.y += 0.3;
	else if (keys->key[S])
		sphere->center.y -= 0.3;
	else if (keys->key[E])
		sphere->center.z += 0.3;
	else if (keys->key[Q])
		sphere->center.z -= 0.3;
}

void	scaling_sphere(t_key *keys, t_sphere *sphere)
{
	if (keys->cur_keycode == LEFT && sphere->radius - 0.1 > 0)
		sphere->radius -= 0.1;
	else if (keys->cur_keycode == RIGHT)
		sphere->radius += 0.1;
}
