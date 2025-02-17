/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:13:15 by likong            #+#    #+#             */
/*   Updated: 2024/12/31 12:25:06 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//May need to check more later
static inline bool	update_hit(t_ray *ray, t_bvh *node, t_hit *hit)
{
	if (is_intersect(node->shapes, ray, hit))
	{
		return (true);
	}
	return (false);
}

static inline bool	next_node(t_ray *ray, t_bvh *node, t_hit *hit)
{
	t_hit	left_hit;
	t_hit	right_hit;
	bool	check_left;
	bool	check_right;

	left_hit = init_hit();
	right_hit = init_hit();
	check_left = check_bvh_intersection(ray, node->left, &left_hit);
	check_right = check_bvh_intersection(ray, node->right, &right_hit);
	if (check_left && !check_right)
	{
		*hit = left_hit;
		return (true);
	}
	else if (check_right)
	{
		*hit = right_hit;
		return (true);
	}
	return (false);
}

bool	check_aabb_intersection(t_ray ray, t_aabb box, double max_t)
{
	double	t1;
	double	t2;
	double	t_min;
	double	t_max;

	t1 = (box.min.x - ray.start.x) * ray.inv_start.x;
	t2 = (box.max.x - ray.start.x) * ray.inv_start.x;
	t_min = fmin(t1, t2);
	t_max = fmax(t1, t2);
	t1 = (box.min.y - ray.start.y) * ray.inv_start.y;
	t2 = (box.max.y - ray.start.y) * ray.inv_start.y;
	t_min = fmax(t_min, fmin(t1, t2));
	t_max = fmin(t_max, fmax(t1, t2));
	t1 = (box.min.z - ray.start.z) * ray.inv_start.z;
	t2 = (box.max.z - ray.start.z) * ray.inv_start.z;
	t_min = fmax(t_min, fmin(t1, t2));
	t_max = fmin(t_max, fmax(t1, t2));
	return (t_max >= fmax(0.0, t_min) && t_min < max_t);
}

bool	check_bvh_intersection(t_ray *ray, t_bvh *node, t_hit *pre_hit)
{
	t_hit	hit;
	bool	check_hit;

	check_hit = false;
	hit = init_hit();
	if (!node)
		return (false);
	if (!check_aabb_intersection(*ray, node->box, hit.distance))
		return (false);
	if (node->shapes)
		check_hit = update_hit(ray, node, &hit);
	else
		check_hit = next_node(ray, node, &hit);
	if (check_hit)
		*pre_hit = hit;
	return (check_hit);
}
