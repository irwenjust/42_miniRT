

#ifndef STRUCTURE_BONUS_H
# define STRUCTURE_BONUS_H

#include "miniRT_bonus.h"

typedef struct s_thread_data
{
	int		start_x;
	int		end_x;
	int		start_y;	
	int		end_y;
}	t_thread_data;

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
} t_key_action;

//shape type
typedef enum	s_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
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

typedef struct s_aabb
{
	t_vector	min;
	t_vector	max;
}	t_aabb;

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

/*custom structure to store image data and size*/
typedef struct s_image
{
	void	*img_ptr;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;


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
	t_vector	normal;
	double		radius;
	t_color		color;
	// t_aabb		box;
	// t_aabb		(*rebuildbox)(struct s_sphere *shape);
}	t_sphere;

typedef struct s_plane
{
	t_vector	center;
	t_vector	normal;
	t_color		color;
}	t_plane;

//cap_s start
//cap_e end
typedef struct s_cylinder
{
	t_vector	center;
	t_vector	normal;
	double		radius;
	double		height;
	t_color		color;
	t_vector	cap_s;
	t_vector	cap_e;
	// t_aabb		box;
	// t_aabb		(*rebuildbox)(struct s_cylinder *shape);
}	t_cylinder;

//normal from tip to base
typedef struct s_cone
{
	t_vector	tip;
	t_vector	base;
	t_vector	center;
	t_vector	normal;
	double		radius;
	double		height;
	double		angle;
	t_color		color;
}	t_cone;


//shape manage
typedef union s_shape_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_cone		cone;
}	t_shape_data;

typedef struct s_shape
{
	int				id;
	t_aabb			box;
	t_shape_type	type;
	t_shape_data	data;
	int				shape_id[4];
	int				depth;
	double			ks;
	double			shininess;
	double			refra_idx;
	double			transparency;
	t_vector		u_axis;
	t_vector		v_axis;
	t_image			*cboard;
	t_image			*tex;
	t_image			*bmp;
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
	t_vector	start;
	t_vector	normal;
	t_vector	inv_start;
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
 * @param check_hit Check hit exist or not
 */
typedef struct s_hit
{
	t_shape	*shape;
	t_ray	ray;
	t_vector	hit_point;
	t_vector	hit_normal;
	t_color	color;
	t_vector	cy_hp;
	t_vector	co_hp;
	double	distance;
	double	refra_idx;
	double	refractivity;
	bool	check_hit;
	bool	side;
	double	u;
	double	v;
	int		depth;
	int		reflect_depth;
} t_hit;


/*macro struct*/
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



typedef struct s_key
{
	int key[256];
	int cur_keycode;
	int action;
	int is_pressed;
} t_key;

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
	char		**args; //map
	t_ambient	ambient;
	t_camera	camera;
	t_fclass	*light;
	t_fclass	*shapes;
	int 		shape_nbr[4]; // notsure
	t_ambient	ori_ambient;
	t_camera	ori_camera;
	t_fclass	*ori_light;
	t_fclass	*ori_shapes;
	t_key 		keys; //not sure
	t_menu		menu; //not sure
	int			select; //not sure
	int			select_rgb;
	int			preset; //for test
	double		view_w;
	double		view_h;
	t_vector	normal_w; //go right
	t_vector	normal_h; //go down
	t_windows	win;
	struct timeval last_frame_time;
	int			bvh_level; // the index level for bvh binary tree
	t_list		*unbound; // for plane and maybe more things later
	t_bvh		*bvh;
}	t_scene;

#endif
