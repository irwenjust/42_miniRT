/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:51 by likong            #+#    #+#             */
/*   Updated: 2025/02/18 10:07:03 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "miniRT.h"

/*enum*/
//menu mode
typedef enum s_menu
{
	VIEW,
	CAMERA,
	LIGHT,
	SHAPE,
}	t_menu;

//key action
typedef enum s_key_action
{
	NOTHING,
	MENU,
	MOVEMENT,
	ROTATION,
	SELECT,
	SCALING,
	PRESET,
	RESET,
	COLOR,
	QUIT
}	t_key_action;

//shape type
typedef enum s_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_shape_type;

/*structure*/
/*basic*/
//vector and coordinate struct
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

//color struct
typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
}	t_color;

typedef struct s_aabb
{
	t_vector	min;
	t_vector	max;
}	t_aabb;

/*fclass and entities*/
//fclass
typedef struct s_fclass
{
	int		size;
	void	**array;
	void	*(*cpy)(void *);
	int		(*cmp)(void *, void *);
	void	(*print)(void *);
	void	(*del)(void *);
}	t_fclass;

/*env part*/
//env light
typedef struct s_ambient
{
	double		brightness;
	t_color		color;
}	t_ambient;

/*camera struct
FOV : Horizontal field of view in degrees in range [0,180]:
*/
typedef struct s_camera
{
	t_vector	coordinate;
	t_vector	normal;
	int			fov;
}	t_camera;

//light
typedef struct s_light
{
	t_vector	point;
	double		brightness;
	t_color		color;
}	t_light;

/*shape part*/
//entities
typedef struct s_sphere
{
	t_vector	center;
	double		radius;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_vector	center;
	t_vector	normal;
	t_color		color;
}	t_plane;

//normal: center -> cap_e
typedef struct s_cylinder
{
	t_vector	center;
	t_vector	normal;
	double		radius;
	double		height;
	t_color		color;
	t_vector	cap_s;
	t_vector	cap_e;
}	t_cylinder;

//shape manage
typedef union s_shape_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_shape_data;

typedef struct s_shape
{
	int				id;
	t_aabb			box;
	t_shape_type	type;
	t_shape_data	data;
	int				shape_id[3];
}	t_shape;

/**
 * @brief equation structrue
 * @param t scalar parameter, how far it traversal along the ray
 */
typedef struct s_equation
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
}	t_equation;

/*render struct*/
typedef struct s_ray
{
	t_vector	start;
	t_vector	normal;
	t_vector	inv_start;
}	t_ray;

/**
 * @brief Describes an intersection point in the scene between 
 * a ray and a shape.
 * 
 * @param shape The shape that was hit
 * @param ray The ray that hit the shape
 * @param hit_point The intersection point
 * @param hit_normal The normal of the shape in the intersection point
 * @param color The color of the hit shape
 * @param cy_hp Used to know where the ray hit in a cylinder's axis
 * @param distance The distance between the hit the ray's origin
 * @param check_hit Check hit exist or not
 */
typedef struct s_hit
{
	t_shape		*shape;
	t_ray		ray;
	t_vector	hit_point;
	t_vector	hit_normal;
	t_color		color;
	t_vector	cy_hp;
	double		distance;
	bool		check_hit;
}	t_hit;

/*macro struct*/
typedef struct s_windows
{
	void	*mlx;
	void	*disp;
	void	*img;
	void	*menu;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_len;
	int		endian;
}	t_windows;

typedef struct s_key
{
	int	key[256];
	int	cur_keycode;
	int	action;
	int	is_pressed;
}	t_key;

typedef struct s_bvh
{
	int				id;
	t_aabb			box;
	t_shape			*shapes;
	struct s_bvh	*left;
	struct s_bvh	*right;
}	t_bvh;

typedef struct s_scene
{
	char			**args;
	t_ambient		ambient;
	t_camera		camera;
	t_fclass		*light;
	t_fclass		*shapes;
	int				shape_nbr[3];
	t_ambient		ori_ambient;
	t_camera		ori_camera;
	t_fclass		*ori_light;
	t_fclass		*ori_shapes;
	t_key			keys;
	t_menu			menu;
	int				select;
	int				select_rgb;
	int				preset;
	double			view_w;
	double			view_h;
	double			view_invw;
	double			view_invh;
	t_vector		normal_w;
	t_vector		normal_h;
	t_vector		vec_min;
	t_windows		win;
	int				bvh_level;
	t_bvh			*bvh;
}	t_scene;

#endif
