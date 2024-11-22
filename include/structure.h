/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:51 by likong            #+#    #+#             */
/*   Updated: 2024/11/22 11:30:55 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

#include "miniRT.h"

/*enum*/
//shape type
typedef enum	s_shape_type
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
	int green;
	int	blue;
	int	alpha;
}	t_color;


/*fclass and entities*/
//fclass
typedef struct	s_fclass
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

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	normal;
	double		radius;
	double		height;
	t_color		color;
	t_vector	cap_u;
	t_vector	cap_b;
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
	t_shape_type	type;
	t_shape_data	data;
	int shape_id[3];
	
}	t_shape;

/**
 * @brief equation structrue
 * @param t scalar parameter, how far it traversal along the ray
 */
typedef struct s_equation
{
	double a;
	double b;
	double c;
	double t1;
	double t2;
} t_equation;

/*render struct*/
typedef struct s_ray
{
	t_vector start;
	t_vector normal;
} t_ray;

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
 */
typedef struct s_hit
{
	t_shape	*shape;
	t_ray	ray;
	t_vector	hit_point;
	t_vector	hit_normal;
	t_color	color;
	t_vector	cy_hp;
	double	distance;
} t_hit;

typedef enum s_mode
{
	VIEW,
	CAMERA,
	LIGHT,
	SHAPE
}	t_mode;

/*macro struct*/
typedef struct s_menu
{
	t_mode mode;
	
} t_menu;

typedef struct s_windows
{
	// mlx_t	*mlx;
	// mlx_image_t	*img;
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

typedef struct s_scene
{
	char		**args; //map
	t_fclass	*light;
	t_fclass	*shapes;
	int shape_nbr[3];
	t_ambient	ambient;
	t_camera	camera;
	t_menu		menu;
	int			select;
	double		view_w;
	double		view_h;
	t_vector	normal_w; //go right
	t_vector	normal_h; //go down
	t_windows	win;
	struct timeval last_frame_time;
	
}	t_scene;



#endif
