/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:51 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 18:27:33 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

#include "miniRT.h"

typedef enum	s_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_shape_type;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_color
{
	int	red;
	int green;
	int	blue;
}	t_color;

typedef struct	s_fclass
{
	int		size;
	void	**array;
	void	*(*cpy)(void *);
	int		(*cmp)(void *, void *);
	void	(*print)(void *);
	void	(*del)(void *);
}	t_fclass;

typedef struct s_ambient
{
	double		brightness;
	t_color		color;
}	t_ambient;

//FOV : Horizontal field of view in degrees in range [0,180]:
typedef struct s_camera
{
	t_vector	coordinate;
	t_vector	normal;
	int			fov;
}	t_camera;


typedef struct s_light
{
	t_vector	coordinate;
	double		brightness;
	t_color		color;
}	t_light;


typedef struct s_cylinder
{
	t_vector	center;
	t_vector	normal;
	double		radius;
	double		height;
	t_color		color;
}	t_cylinder;


typedef struct s_plane
{
	t_vector	coordinate;
	t_vector	normal;
	t_color		color;
}	t_plane;


typedef struct s_sphere
{
	t_vector	center;
	double		radius;
	t_color		color;
}	t_sphere;


typedef union s_shape_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_shape_data;


typedef struct s_shape
{
	int				id;
	t_shape_type	type;
	t_shape_data	data;
}	t_shape;

typedef struct s_scene
{
	t_fclass	*light;
	t_fclass	*shapes;
	char		**map;
	t_ambient	ambient;
	t_camera	camera;
}	t_scene;

#endif
