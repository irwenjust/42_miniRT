#include "miniRT_bonus.h"

static bool	new_cone(char **arg, t_cone *cone)
{
	char	**tmp;

	tmp = ft_split(arg[1], ',');
	if (!tmp)
		return (ERROR("cone: fail to split tip coordinate"), false);
	cone->tip = parse_vector(tmp);
	free_matrix(tmp);
	tmp = ft_split(arg[2], ',');
	if (!tmp)
		return (ERROR("cone: fail to split normal"), false);
	cone->normal = parse_vector(tmp);
	if (vector_magnitude(cone->normal) < 1.0 - 1e-8)
		return (ERROR("cone: normal vector is too small"), false);
	cone->normal = vector_normalize(cone->normal);
	free_matrix(tmp);
	cone->radius = ft_atod(arg[3]) * 0.5;
	cone->height = ft_atod(arg[4]);
	if (cone->radius < 1e-8 || cone->height < 1e-8)
		return (ERROR("cone: wrong diameter or height value"), false);
	tmp = ft_split(arg[5], ',');
	if (!tmp)
		return (ERROR("cone: fail to split color"), false);
	cone->color = parse_color(tmp);
	free_matrix(tmp);
	return (true);
}

bool	parse_cone(char **arg, t_fclass *fclass)
{
	t_shape	*shape;
	t_cone	cone;

	if (ft_matrix_size(arg) < 9 || ft_matrix_size(arg) > 10 || !check_syntax(arg, "01100100"))
		return (ERROR("cone: wrong args format"), false);
	if (!check_rgb(arg[5]))
		return (ERROR("cone: wrong color value"), false);
	if (!new_cone(arg, &cone))
		return (ERROR("cone: fail to create new cone"), false);
	cone.angle = atan(cone.radius / cone.height) + 1e-8;
	cone.base = vector_add(cone.tip, vector_scale(cone.normal, cone.height));
	cone.center = vector_scale(vector_add(cone.tip, cone.base), 0.5);
	shape = new_shape(&cone, CONE, fclass->size, s()->shape_nbr[CONE]);
	check_texture(arg, shape);
	shape->ks = ft_atod(arg[6]);
	shape->shininess = ft_atod(arg[7]);
	if (shape->ks < 1e-8 || shape->ks > 1)
		return (ERROR("sphere: wrong ks value"), false);
	if (shape->shininess < 1 || shape->shininess > 128)
		return (ERROR("sphere: wrong shininess value"), false);
	// printf("ks %f, shininess %f\n", shape->ks, shape->shininess);
	s()->shape_nbr[CONE]++;
	add_uv_axis(shape, shape->data.cone.normal);
	push_to_fclass(fclass, shape);
	// print_shape(shape);
	return (true);
}

void	move_cone(t_key *keys, t_cone *cone)
{
	if (keys->key[D])
		cone->tip.x += 0.3;
	else if (keys->key[A])
		cone->tip.x -= 0.3;
	if (keys->key[W])
		cone->tip.y += 0.3;
	else if (keys->key[S])
		cone->tip.y -= 0.3;
	else if (keys->key[E])
		cone->tip.z += 0.3;
	else if (keys->key[Q])
		cone->tip.z -= 0.3;
	cone->base = vector_add(cone->tip, vector_scale(cone->normal, cone->height));
	cone->center = vector_scale(vector_add(cone->tip, cone->base), 0.5);
}

void	rotate_cone(t_key *keys, t_cone *cone)
{
	if (keys->key[I])
		cone->normal = vector_rotate(cone->normal, X, ROTATE);
	else if (keys->key[K])
		cone->normal = vector_rotate(cone->normal, X, (-ROTATE));
	else if (keys->key[L])
		cone->normal = vector_rotate(cone->normal, Y, ROTATE);
	else if (keys->key[J])
		cone->normal = vector_rotate(cone->normal, Y, (-ROTATE));
	else if (keys->key[O])
		cone->normal = vector_rotate(cone->normal, Z, ROTATE);
	else if (keys->key[U])
		cone->normal = vector_rotate(cone->normal, Z, (-ROTATE));
	cone->base = vector_add(cone->tip, vector_scale(cone->normal, cone->height));
	cone->center = vector_scale(vector_add(cone->tip, cone->base), 0.5);
}

void	scaling_cone(t_key *keys, t_cone *cone)
{
	if (keys->cur_keycode == LEFT && cone->radius - 0.1 > 0)
		cone->radius -= 0.1;
	else if (keys->cur_keycode == RIGHT)
		cone->radius += 0.1;
	else if (keys->cur_keycode == UP)
		cone->height += 0.1;
	else if (keys->cur_keycode == DOWN && cone->height - 0.1 > 0)
		cone->height -= 0.1;
	cone->angle = atan(cone->radius / cone->height) + 1e-8;
	cone->base = vector_add(cone->tip, vector_scale(cone->normal, cone->height));
	cone->center = vector_scale(vector_add(cone->tip, cone->base), 0.5);
}