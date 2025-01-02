
#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# define SUCCESS 0
# define FAILURE 1

# define FRAME_RATE 60 //Target frame rate (15 fps)
# define FRAME_TIME (1000000 / FRAME_RATE)

# define ROTATE 0.1

# define HAS_COMMA '1'

# define X 0
# define Y 1
# define Z 2

# define MIN(a, b)	((a) * (a < b) + (b) * (b < a))

//about windows setting (16:9)
# define SCALE 0.5625
# define WIDTH 1600
# define HEIGHT (WIDTH * SCALE)
# define INVWIDTH 1.0f / WIDTH
# define INVHEIGHT 1.0f / HEIGHT

# define PI 3.141592653589f
# define RADIAN(angle) ((angle * PI) / 180.0f)

# define UPVECTOR (t_vector){0.0, 1.0, 0.0}
# define VEC_MIN (t_vector){0.0001, 0.0001, 0.0001}

# define ERROR(s) printf("Error: %s\n", s)

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
# include <math.h>
# include <stdint.h>
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
				void (*print)(void *), void (*del)(void *));
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
//parse tool
bool		check_syntax(char **arg, char *commas);
bool		check_rgb(char *rgb);
t_color		parse_color(char **rgb);

/**
 * render
 */
//renderer
void		render(void);
void		fake_render(void);
//control frame rate
void		control_frame_rate(void);
//ray part
t_ray		make_ray(t_vector cur);
t_vector	point_on_ray(t_ray *ray, double t);
//intersect part
bool		check_intersection(t_fclass *shapes, t_ray *ray, t_hit *closest);
bool		is_intersect(t_shape *shape, t_ray *ray, t_hit *inter,
				double *valid_t);
void		find_valid_t(t_equation *equation);
//illumination part
void		check_illumination(t_hit *closest);
//reflect part
t_color		diffuse(t_light *light, t_hit *inter, double k);

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
bool		inter_sphere(t_sphere *sphere, t_ray *ray, t_hit *inter,
				double *valid_t);
void		move_sphere(t_key *keys, t_sphere *sphere);
void		scaling_sphere(t_key *keys, t_sphere *sphere);
//plane part
bool		parse_plane(char **arg, t_fclass *fclass);
bool		inter_plane(t_plane *plane, t_ray *ray, t_hit *inter,
				double *valid_t);
void		move_plane(t_key *keys, t_plane *plane);
void		rotate_plane(t_key *keys, t_plane *plane);
//bool		inter_real_plane(t_plane *plane, t_ray *ray, double *valid_t);
//cylinder part
bool		parse_cylinder(char **arg, t_fclass *fclass);
void		move_cylinder(t_key *keys, t_cylinder *cylinder);
void		rotate_cylinder(t_key *keys, t_cylinder *cylinder);
void		scaling_cylinder(t_key *keys, t_cylinder *cy);
//cylinder inter
bool		inter_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit *inter,
				double *valid_t);

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

/**
 * vector part
 */
//vector op basic
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_sub(t_vector v1, t_vector v2);
t_vector	vector_multiple(t_vector v1, double scalar);
t_vector	vector_min(t_vector a, t_vector b);
t_vector	vector_max(t_vector a, t_vector b);
//vector op plus
double		vector_magnitude(t_vector a);
t_vector	vector_normalize(t_vector a);
t_vector	vector_cross(t_vector v1, t_vector v2);
double		vector_dot(t_vector v1, t_vector v2);
t_vector	vector_scale(t_vector a, double scalar);
//vector rotate
t_vector	vector_rotate(t_vector vec, int axis, double angle);
//vector tools
t_vector	parse_vector(char **strs);
bool		vector_compare(t_vector v1, t_vector v2);
double		vector_cos(t_vector v1, t_vector v2);
t_vector	vector_copy(t_vector vec);

/**
 * tools
 */
//color part
t_color		add_bright_to_color(t_color color, double brightness);
t_color		add_color(t_color c1, t_color c2);
t_color		copy_color(t_color c);
t_color		*get_color(int type, int i);
t_color		mix_color(t_color base, t_color light_effect);
//equation
double		solve(t_equation *equation);
//free the scene
void		delete_scene(void);
//show error message
void		error_exit(char *message);
//others
t_hit		init_hit(void);
void		ft_swap_d(double *a, double *b);
t_shape		**shapes_to_arr(t_shape **shapes);

/**
 * menu
 */
void		display_menu(void);
void		display(int x, int y, int color, char *text);
void		display_clear(int x, int y, int color, char *text);
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
t_aabb		box_sphere(t_sphere *sphere);
t_aabb		box_cylinder(t_cylinder *cy);

/**
 * debug
 */
void		print_shape(t_shape *shape);
void		print_light(t_light *light);
void		print_camera(t_camera *camera);
void		print_box(t_aabb box);

// bool	check_unbound(t_ray *ray, t_hit *inter);

#endif
