/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:25:28 by likong            #+#    #+#             */
/*   Updated: 2024/11/25 09:58:49 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define SUCCESS 0
# define FAILURE 1

# define ESC 65307
# define TAB 65289
// # define SPACE 9
// # define UP 65362
// # define DOWN 65364
// # define LEFT 65361
// # define RIGHT 65363

# define V 118 //view mode
# define C 99 //camera mode
# define B 98 //light bulb mode
# define M 109 //model mode
# define G 103

# define W 119
# define A 97
# define S 115
# define D 100
# define Q 113
# define E 101

# define I 105
# define J 106
# define K 107
# define L 108
# define U 117
# define O 111

# define ONE 49
# define TWO 50
# define THREE 51

# define MENU_KEY "vcbm"
# define PRESET_KEY "123"
# define MOVE_KEY "wasdqe"
# define ROTATE_KEY "ijkluo"

# define FRAME_RATE 60 //Target frame rate (15 fps)
# define FRAME_TIME (1000000 / FRAME_RATE)


# define ROTATE 0.1

# define HAS_COMMA '1'

// # define AMBIENT 0
// # define CAMERA 1
// # define LIGHT 2

// # define R 0
// # define G 1
// # define B 2

# define X 0
# define Y 1
# define Z 2

# define MIN(a, b)	((a) * (a < b) + (b) * (b < a))

//Some standard color
# define BLUE (t_color){137, 196, 244, 0}
# define BLACK		(t_color){0, 0, 0, 0}
# define WHITE		(t_color){0, 255, 255, 255}
# define RED		(t_color){255, 0, 0, 0}
# define GREEN		(t_color){0, 255, 0, 0}

//about windows setting (16:9)
# define SCALE 0.5625
# define WIDTH 1600
# define HEIGHT (WIDTH * SCALE)

# define PI 3.141592653589
# define RADIAN(angle) ((angle * PI) / 180.0f)

# define UPVECTOR (t_vector){0.0, 1.0, 0.0}
# define VEC_MIN (t_vector){0.0001, 0.0001, 0.0001} // The value could consider modify

# define ERROR(s) printf("Error: %s\n", s)

/*
stdio: printf
fcntl: O_RDONLY
stdlib: malloc, free
*/
// #include <MLX42/MLX42.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <sys/time.h>

#include "libft.h"
#include "structure.h"
#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include "../libft/get_next_line/get_next_line.h"

//
t_scene	*s(void);

/*init*/
//initial part
void	init_scene(char *file_name);
//validate
bool	validate_filename(char *f_name);
int		get_nof_validrows(char *file_name);


/*parser*/
void	parse_args();
//parse tool
bool 	check_syntax(char **arg, char *commas);
bool 	check_rgb(char *rgb);
//color part
t_color	parse_color(char **rgb);
t_color	add_bright_to_color(t_color color, double brightness);
t_color	add_color(t_color c1, t_color c2);


/*render*/
//renderer
void	render();
void	fake_render();
//control frame rate
void	control_frame_rate();
//ray part
t_ray make_ray(t_vector cur);
t_vector	point_on_ray(t_ray *ray, double t);
//intersect part
bool	check_intersection(t_fclass *shapes, t_ray *ray, t_hit *closest);
bool	is_intersect(t_shape *shape, t_ray *ray, t_hit *inter);
//illumination part
void	check_illumination(t_hit *closest);
//reflect part
t_color	diffuse(t_light *light, t_hit *inter, double k);


/*entities*/
//ambient part
bool	parse_ambient(int counter[3], char **tmp, t_ambient *ambient);
t_color	check_ambient(t_color color);
//camera part
t_camera copy_camera(t_camera camera);
bool	parse_camera(int counter[3], char **tmp, t_camera *camera);
//light part
bool	parse_light(int counter[3], char **arg, t_fclass *light);
t_light	*copy_light(t_light *light);
//shape part
t_shape	*copy_shape(t_shape *shape);
t_shape	*new_shape(void *data, t_shape_type type, int id, int shape_id);
//sphere part
bool	parse_sphere(char **tmp, t_fclass *fclass);
bool	inter_sphere(t_sphere *sphere, t_ray *ray, t_hit *inter);
//plane part
bool parse_plane(char **arg, t_fclass *fclass);
bool inter_plane(t_plane *plane, t_ray *ray, t_hit *inter);
//cylinder part
bool parse_cylinder(char **arg, t_fclass *fclass);
bool inter_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit *inter);
//cylinder tool
double	check_cy_hit(t_cylinder *cy, t_ray *ray, t_equation *eq, t_hit *inter);


/**key hook */
//key 
int press_key(int keycode, t_key *keys);
int release_key(int keycode, t_key *keys);
//update
int update(t_key *keys);
void update_move(t_key *keys);
void update_rotate(t_key *keys);
int		ft_quit();
//move shape
void move_sphere(t_key *keys, t_sphere *sphere);
void move_plane(t_key *keys, t_plane *plane);
void move_cylinder(t_key *keys, t_cylinder *cylinder);
//rotate shape
void rotate_plane(t_key *keys, t_plane *plane);
void rotate_cylinder(t_key *keys, t_cylinder *cylinder);


/*vector part*/
//vector op basic
t_vector		vector_add(t_vector v1, t_vector v2);
t_vector		vector_sub(t_vector v1, t_vector v2);
t_vector	vector_multiple(t_vector v1, double scalar);
//vector op plus
double			vector_magnitude(t_vector a);
t_vector		vector_normalize(t_vector a);
t_vector		vector_cross(t_vector v1, t_vector v2);
double			vector_dot(t_vector v1, t_vector v2);
//vector rotate
t_vector	vector_rotate(t_vector vec, int axis, double angle);
//vector tools
t_vector		parse_vector(char **strs);
bool	vector_compare(t_vector v1, t_vector v2);
double			vector_cos(t_vector v1, t_vector v2);
t_vector vector_copy(t_vector vec);


/*tools*/
//equation
bool solve(t_equation *equation);

/*menu*/
void display_menu();
//menu display tool
void	display(int x, int y, int color, char *text);
void display_move_rotate(int x, int y);
void display_mode(int x, int y);
void display_shape(int x, int y);
void display_light(int x, int y);


//free the scene
void	delete_scene();

//show error message
void	error_exit(char *message);
t_camera copy_camera(t_camera camera);

void backup_scene();





//New function for fake class
t_fclass	*fclass_new(void *(*cpy)(void *), int (*cmp)(void *, void *),
	void (*print)(void *), void (*del)(void *));
void		push_to_fclass(t_fclass *fclass, void *element);
void		*fclass_index(t_fclass *fclass, int i);

//debug part
void	print_shape(t_shape *shape);
void	print_light(t_light *light);
void print_camera(t_camera *camera);

#endif