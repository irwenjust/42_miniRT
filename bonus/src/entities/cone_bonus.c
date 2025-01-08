#include "miniRT_bonus.h"

	t_vector	tip;
	t_vector	base;
	t_vector	normal;
	double		radius;
	double		height;
	double		angle;
	t_color		color;

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
	cone->normal = vector_normalize(parse_vector(tmp));
	if (vector_magnitude(cy->normal) < 1.0 - 1e-8)
		return (ERROR("cone: normal vector is too small"), false);
	free_matrix(tmp);
	cone->radius = ft_atod(arg[3]) * 0.5;
	cone->height = ft_atod(arg[4]);
	if (cone->radius < 1e-8 || cone->height < 1e-8)
		return (ERROR("cone: wrong diameter or height value"), false);
	tmp = ft_split(arg[5], ',');
	if (!tmp)
		return (ERROR("cone: fail to split color"), false);
	cy->color = parse_color(tmp);
	free_matrix(tmp);
	return (true);
}

bool	parse_cone(char **arg, t_fclass *fclass)
{
	t_shape	*shape;
	t_cone	cone;

	if (ft_matrix_size(arg) != 8 || !check_syntax(arg, "01100100"))
		return (ERROR("cone: wrong args format"), false);
	if (ft_atod(arg[3]) * 0.5 < 1e-8)
		return (ERROR("cone: wrong diameter value"), false);
	if (ft_atod(arg[4]) < 1e-8)
		return (ERROR("cone: wrong height value"), false);
	if (!check_rgb(arg[5]))
		return (ERROR("cone: wrong color value"), false);
	if (!new_cone(arg, &cone))
		return (ERROR("cone: fail to create new cone"), false);
}