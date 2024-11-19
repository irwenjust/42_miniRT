/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:38:02 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/18 14:34:04 by likong           ###   ########.fr       */
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
	cylinder->radius = ft_atod(arg[3]) / 2.0;
	cylinder->height = ft_atod(arg[4]);
	rgb = ft_split(arg[5], ',');
	if (!rgb)
		return (ERROR("cylinder: fail to split color"), false);
	cylinder->color = parse_color(rgb);
	free_matrix(rgb);
	return (true);
}

bool parse_cylinder(char **arg, t_fclass *fclass)
{
	t_shape *shape;
	t_cylinder cylinder;

	if (ft_matrix_size(arg) != 6 || !check_syntax(arg, "011001"))
		return (ERROR("cylinder: wrong args format"), false);
	if (ft_atod(arg[3]) / 2.0 < 1e-8)
		return (ERROR("cylinder: wrong radius value"), false);
	if (ft_atod(arg[4]) < 1e-8)
		return (ERROR("cylinder: wrong height value"), false);
	if (!check_rgb(arg[5]))
		return (ERROR("cylinder: wrong color value"), false);
	if (!new_cylinder(arg, &cylinder))
		return (ERROR("cylinder: fail to create new shpere"), false);
	cylinder.cap_u = vector_add(cylinder.center, vector_multiple(cylinder.normal, -cylinder.height / 2.0));
	cylinder.cap_b = vector_add(cylinder.center, vector_multiple(cylinder.normal, cylinder.height / 2.0));
	shape = new_shape(&cylinder, CYLINDER, fclass->size);
	push_to_fclass(fclass, shape);
	return (true);
}

/**
 * @brief
 * cylinder equation is |(P-C) - [(P-C)*N]*N|^2 = r^2
 * 		P is a point on the cylinder surface
 * 		C is a point on the cylinder axis(cap)
 * 		N is cylinder direction
 * P is the R(t) = O + tD
 * The eqaution is: |(O + tD - C) - [(O + tD - C)*N]*N|^2 = r^2
 * set V = O-C
 * 		|V + tD - (V*N + tD*N)*N|^2 - r^2 = 0
 * 		|t[D - (D*N)N] + [V-(V*N)N]|^2 - r^2 = 0
 * 		t^2*[D-(D*N)N]^2 + 2t*[D-(D*N)N]*[V-(V*N)N] + [V-(V*N)N]^2 -r^2 = 0
 * So at^2 + bt + c = 0:
 * 		a = [D-(D*N)N]^2 = D*D -2(D*N)^2 + (D*N)^2*N^2
 * 		b = 2*[D-(D*N)N]*[V-(V*N)N] = 2*(D*V - D(V*N)N -V(D*N)N + (D*N)(V*N)*N^2
 * 		c = [V-(V*N)N]^2 -r^2 = V^2 - 2(V*N)^2 + (V*N)^2*N^2 - r^2
 * as normal * normal = 1, so D*D = N*N = 1
 * 		a = 1 - (D*N)^2
 * 		b = 2 * [D*V - (D*N)(V*N)]
 * 		c = V^2 - (V*N)^2 - r^2
 * 
 * @param vec vector from ray origin to cylinder cap center
 * @param dn dot_product(D, N), D is ray normal, N is cylinder norml
 * @param vn dot_product(vec, N) 
 */
bool inter_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit *inter)
{
	t_equation equation;
	t_vector vec;
	double dn;
	double vn;
	double distance;

	vec = vector_sub(ray->start, cylinder->cap_u);
	dn = vector_dot(ray->normal, cylinder->normal);
	vn = vector_dot(vec, cylinder->normal);
	equation.a = 1 - pow(dn, 2);
	equation.b = 2 * (vector_dot(ray->normal, vec) - (dn * vn));
	equation.c = vector_dot(vec, vec) - pow(vn, 2) - pow(cylinder->radius, 2);
	equation.t1 = -1;
	equation.t2 = -1;
	if (solve(&equation) && (equation.t1 > 1e-8 || equation.t2 > 1e-8))
	{
		distance = check_cy_hit(cylinder, ray, &equation, inter);
		if (distance > 0.0f)
		{
			inter->distance = distance;
			inter->color = cylinder->color;
			return (true);
		}
	}
	return (false);
}
