/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:59:07 by likong            #+#    #+#             */
/*   Updated: 2025/02/18 13:48:36 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# define NUM_THREADS 24

# define SUCCESS 0
# define FAILURE 1

# define RAND_MAX 2147483647

# define INSIDE 0
# define OUTSIDE 1

# define FRAME_RATE 25
//(1000000 / FRAME_RATE)
# define FRAME_TIME 40000

# define ROTATE 0.1

# define HAS_COMMA '1'
# define NOT_NBR '2'

# define X 0
# define Y 1
# define Z 2

//about windows setting (16:9)
# define WIDTH 160
# define HEIGHT 90

# define PI 3.141592653589f

/*
stdio: printf
fcntl: O_RDONLY
stdlib: malloc, free
*/
// #include <MLX42/MLX42.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <X11/X.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line/get_next_line.h"
# include "structure_bonus.h"
# include "preset_bonus.h"

/**
 * fake global func
 */
t_scene		*s(void);

/**
 * flacss
 */
//New function for fake class
t_fclass	*fclass_new(void *(*cpy)(void *), int (*cmp)(void *, void *),
				void (*del)(void *), void (*print)(void *));
void		push_to_fclass(t_fclass *fclass, void *element);
void		*fclass_index(t_fclass *fclass, int i);

/**
 * init
 */
//initial part
void		init_scene(char *file_name);
void		init_viewport(void);
//validate
bool		validate_filename(char *f_name);
int			get_nof_validrows(char *file_name);
void		backup_scene(void);

/**
 * parser
 */
void		parse_args(void);
//validate
bool		validate_ambient(char **arg);
bool		validate_camera(char **arg);
bool		validate_light(char **arg);
bool		validate_sphere(char **arg);
bool		validate_plane(char **arg);
bool		validate_cylinder(char **arg);
bool		validate_cone(char **arg);
//parse tool
bool		check_arg_format(char **arg, char *arg_type);
bool		check_rgb(char *rgb);
t_color		parse_color(char **rgb);

/**
 * render
 */
//renderer
void		render(int fake);
//control frame rate
void		control_frame_rate(void);
//ray part
t_ray		make_ray(t_vector cur);
t_vector	point_on_ray(t_ray *ray, double t);
void		ray_tracer(t_ray *ray, t_hit *hit, int status);
//intersect part
bool		check_intersection(t_fclass *shapes, t_ray *ray, t_hit *closest);
bool		is_intersect(t_shape *shape, t_ray *ray, t_hit *inter);
void		find_valid_t(t_equation *equation);
//illumination part
void		phong_illumination(t_hit *closest);
//tools
double		calculate_fresnel(t_hit *hit);
t_hit		generate_hit(void);
double		calculate_reflectance(double cos_theta, double n1, double n2);
//reflection
void		set_reflection_ray(t_ray *ray, t_ray *reflect_ray, t_hit *hit);
void		add_reflect_color(t_hit *hit, t_hit *reflect_hit);
//refraction part
void		check_refraction(t_ray *refract_ray, t_hit *hit);
void		set_refraction_ray(t_ray *ray, t_ray *refract_ray, t_hit *hit);
void		add_refract_color(t_hit *hit, t_hit *refract_hit);

/**
 * intersection
 */
bool		inter_sphere(t_sphere *sphere, t_ray *ray, t_hit *inter);
bool		inter_plane(t_plane *plane, t_ray *ray, t_hit *inter);
bool		inter_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit *inter);
bool		inter_cone(t_cone *cone, t_ray *ray, t_hit *hit);

/**
 * entities
 */
//ambient part
bool		parse_ambient(int counter[3], char **tmp, t_ambient *ambient);
t_color		check_ambient(t_color color);
t_ambient	copy_ambient(t_ambient ambient);
//camera part
t_camera	copy_camera(t_camera camera);
bool		parse_camera(char **tmp, t_camera *camera);
void		move_camera(t_key *keys);
void		rotate_camera(t_key *keys);
void		update_camera_fov(t_key *keys);
//light part
t_light		*copy_light(t_light *light);
bool		parse_light(int counter[3], char **arg, t_fclass *light);
void		move_light(t_key *keys, t_light *light);
//shape part
t_shape		*copy_shape(t_shape *shape);
t_shape		*new_shape(void *data, t_shape_type type, int id, int shape_id);
void		move_shape(t_key *keys, t_shape *shape);
void		rotate_shape(t_key *keys, t_shape *shape);
//sphere part
bool		parse_sphere(char **tmp, t_fclass *fclass);
void		move_sphere(t_key *keys, t_sphere *sphere);
void		scaling_sphere(t_key *keys, t_sphere *sphere);
void		rotate_sphere(t_key *keys, t_sphere *sphere);
//plane part
bool		parse_plane(char **arg, t_fclass *fclass);
void		move_plane(t_key *keys, t_plane *plane);
void		rotate_plane(t_key *keys, t_plane *plane);
//cylinder part
bool		parse_cylinder(char **arg, t_fclass *fclass);
void		move_cylinder(t_key *keys, t_cylinder *cylinder);
void		rotate_cylinder(t_key *keys, t_cylinder *cylinder);
void		scaling_cylinder(t_key *keys, t_cylinder *cy);
//cone
bool		parse_cone(char **arg, t_fclass *fclass);
void		move_cone(t_key *keys, t_cone *cone);
void		rotate_cone(t_key *keys, t_cone *cone);
void		scaling_cone(t_key *keys, t_cone *cone);

/**
 * key hook
 */
//key 
int			press_key(int keycode, t_key *keys);
int			release_key(int keycode, t_key *keys);
int			ft_quit(void);
int			update(t_key *keys);
//click action
void		update_menu(t_key *keys);
void		update_preset(t_key *keys);
void		update_reset(t_key *keys);
void		update_select(t_key *keys);
//hold action
void		update_scaling(t_key *keys);
void		update_move(t_key *keys);
void		update_rotate(t_key *keys);
void		update_color(t_key *keys);
//preset part
void		switch_preset(int preset);
void		camera_preset(int preset);
//reset part
void		reset_all(void);
void		reset_camera(void);
void		reset_lights(void);
void		reset_shapes(void);

/**
 * menu
 */
void		display_menu(void);
void		display(int x, int y, int color, char *text);
void		display_f(int x, int y, int color, char *text);
//menu
void		view_menu(int ori_x, int y);
void		camera_menu(int ori_x, int y);
void		light_menu(int ori_x, int y);
void		shape_menu(int ori_x, int y);
//menu display tool
void		display_move_rotate_size(int x, int y);
void		display_color(int x, int y, t_color *rgb);
void		display_brightness(int x, int y, double brightness);
void		display_mode(int x, int y);

/**
 * bvh
 */
//bvh tool functions
t_aabb		generate_box(t_shape **shapes, int amount);
int			find_max_axis(t_aabb box);
int			split_box(int axis, t_shape **shapes, int amount);
void		free_bvh(t_bvh **bvh);
void		rebuild_bvh(void);
//aabb intersection check
bool		check_aabb_intersection(t_ray ray, t_aabb box, double max_t);
bool		check_bvh_intersection(t_ray *ray, t_bvh *node, t_hit *pre_hit);
//aabb box
t_aabb		shape_box(t_shape *shape);

/**
 * vector part
 */
//vector op basic
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_sub(t_vector v1, t_vector v2);
t_vector	vector_scale(t_vector a, double scalar);
t_vector	vector_min(t_vector a, t_vector b);
t_vector	vector_max(t_vector a, t_vector b);
//vector op plus
double		vector_magnitude(t_vector a);
t_vector	vector_normalize(t_vector a);
t_vector	vector_cross(t_vector v1, t_vector v2);
double		vector_dot(t_vector v1, t_vector v2);
//vector rotate
t_vector	vector_rotate(t_vector vec, int axis, double angle);
//vector tools
t_vector	parse_vector(char **strs);
bool		vector_compare(t_vector v1, t_vector v2);
double		vector_cos(t_vector v1, t_vector v2);
t_vector	vector_copy(t_vector vec);

/**
 * color
 */
//color calculation
t_color		add_color(t_color c1, t_color c2);
t_color		sub_color(t_color c1, t_color c2);
t_color		multi_color(t_color color, double factor);
t_color		mix_color(t_color c1, t_color c2);
//color utils
t_color		hex_to_color(unsigned int hex);
void		put_pixel(t_color c, int x, int y);
t_color		copy_color(t_color c);
t_color		*get_color(int type, int i);
void		put_test_pixel(t_image *img, int i, int j, t_color color);
//bump texture part
void		check_bump(t_hit *hit);
//texture part
t_color		add_texture(t_hit *hit);
bool		check_texture(char **arg, t_shape *shape);
//image part
bool		init_image(t_image *img, int width, int height);
bool		load_image(t_image *img, char *path);

/**
 * tools
 */
//math
double		solve(t_equation *equation);
double		ft_rand(void);
void		ft_swap_d(double *a, double *b);
//free the scene
void		delete_scene(void);
//show error message
void		error_exit(char *message);
void		ft_free(void **ptr);
void		error(char *str);

//others
t_shape		**shapes_to_arr(t_shape **shapes);
char		*save_str_without_newline(char *str);
t_hit		init_hit(void);
void		check_hit(t_hit *hit);
double		calculate_radius(double angle);

/**
 * debug
 */
void		print_shape(t_shape *shape);
void		print_light(t_light *light);
void		print_camera(t_camera *camera);
void		print_box(t_aabb box);

//check normal in different type
void		check_hit_normal(t_hit *hit);
void		find_uv(t_hit *hit);
void		add_uv_axis(t_shape *shape, t_vector normal);
t_color		uv_get_color(t_image *img, double u, double v);
void		uv_repeat_wrap(double *u, double *v, int repeat);

//uv for different shape
void		cone_uv(t_hit *hit, double *u, double *v, int repeat);
void		cylinder_uv(t_hit *hit, double *u, double *v, int repeat);
void		sphere_uv(t_hit *hit, double *u, double *v, int repeat);
void		plane_uv(t_hit *hit, double *u, double *v, int repeat);

//uv tools
void		rotate_uv(t_key *keys, t_shape *shape);
t_color		get_pixel(t_image img, int x, int y);

//normal part
t_vector	cone_normal(t_hit *inter);
t_vector	cylinder_normal(t_hit *inter);
t_vector	sphere_normal(t_hit *inter);

#endif
