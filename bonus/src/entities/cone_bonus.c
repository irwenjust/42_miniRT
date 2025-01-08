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

	if (ft_matrix_size(arg) != 8 || !check_syntax(arg, "01100100"))
		return (ERROR("cone: wrong args format"), false);
	if (!check_rgb(arg[5]))
		return (ERROR("cone: wrong color value"), false);
	if (!new_cone(arg, &cone))
		return (ERROR("cone: fail to create new cone"), false);
	cone.angle = atan(cone.radius / cone.height) + 1e-8;
	cone.base = vector_add(cone.tip, vector_multi(cone.normal, cone.height));
	shape = new_shape(&cone, CONE, fclass->size, s()->shape_nbr[CONE]);
	shape->ks = ft_atod(arg[6]);
	shape->shininess = ft_atod(arg[7]);
	if (shape->ks < 1e-8 || shape->ks > 1)
		return (ERROR("sphere: wrong ks value"), false);
	if (shape->shininess < 1 || shape->shininess > 128)
		return (ERROR("sphere: wrong shininess value"), false);
	printf("ks %f, shininess %f\n", shape->ks, shape->shininess);
	s()->shape_nbr[CONE]++;
	push_to_fclass(fclass, shape);
	print_shape(shape);
	return (true);
}
