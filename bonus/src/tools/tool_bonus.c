

#include "miniRT_bonus.h"

t_shape	**shapes_to_arr(t_shape **shapes)
{
	t_shape	**res;
	int		i;

	i = -1;
	res = ft_calloc(s()->shapes->size, sizeof(t_shape *));
	while (shapes[++i])
		res[i] = shapes[i];
	return (res);
}

void	ft_swap_d(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

t_hit	init_hit(void)
{
	static t_hit	hit;
	static bool		init = true;

	if (init)
	{
		ft_bzero(&hit, sizeof(t_hit));
		// hit.color = BLACK;
		hit.distance = INFINITY;
		hit.shape = NULL;
		init = false;
	}
	return (hit);
}

void	check_hit(t_hit *hit)
{
	hit->hit_point = vector_add(hit->ray.start, vector_scale(hit->ray.normal, hit->distance));
	check_hit_normal(hit);
	find_uv(hit);
}
