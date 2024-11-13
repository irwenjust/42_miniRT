/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:46 by likong            #+#    #+#             */
/*   Updated: 2024/10/29 15:21:15 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"



//void	draw_image()
//{
//	int	x;
//	int y;
//	y = -1;
//	while (++y < HEIGHT)
//	{
//		x = -1;
//		while (++x < WIDTH)
//			put_pixel(BLUE, x, y);
//	}
//	mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.img, 0, 0);
//}

t_vector	convert_viewport(int x, int y)
{
	t_vector	converted;

	converted.x = ((2.0f * x) / WIDTH) - 1; //why 2.0f
	converted.y = ((2.0f * y) / HEIGHT) - 1;
	converted.z = 0;
	return (converted);
}

t_ray make_ray(t_vector viewport)
{
	t_ray ray;
	t_vector vertical;
	t_vector horizontal;
	t_vector tmp;

	//view point position on viewport
	vertical = vector_multiple(s()->vec_h, viewport.y * s()->h_view);
	horizontal = vector_multiple(s()->vec_w, viewport.x * s()->w_view);

	tmp = vector_add(vertical, horizontal); //from viewport (0,0,0) to cur(x, y, 0)
	tmp = vector_add(tmp, s()->camera.normal); //from cur viewport(x, y) to camera direction
	tmp = vector_add(tmp, s()->camera.coordinate); //??
	ray.point = s()->camera.coordinate;
	ray.direct = vector_normalize(vector_subtract(tmp, ray.point));
	return (ray);
}

void draw_image()
{
	t_vector cur; //current point on screen viewport
	t_hit closest; //the closest shape
	t_vector viewport;
	t_ray ray;

	cur.y = -1;
	while (++cur.y < HEIGHT)
	{
		cur.x = -1;
		while (++cur.x < WIDTH)
		{
			//init
			closest.color = BLACK;
			closest.shape = NULL;
			closest.distance = INFINITY;
		//1-3d coordinate of viewport
			viewport = convert_viewport(cur.x, cur.y); //why??????????????
		//2-ray from cerama to viewport
			ray = make_ray(viewport);
		//3-check whether the ray is intersect with shape
			//check_intersect();
		//4-if intersect, update closest color based on other env
			put_pixel(closest.color, cur.x, cur.y);
		}
	}
	mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.img, 0, 0);
}