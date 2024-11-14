/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:25:28 by likong            #+#    #+#             */
/*   Updated: 2024/10/29 15:20:42 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define SUCCESS 0
# define FAILURE 1

# define ESC 65307

# define HAS_COMMA '1'

# define AMBIENT 0
# define CAMERA 1
# define LIGHT 2

# define R 0
# define G 1
# define B 2

# define X 0
# define Y 1
# define Z 2

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
bool check_syntax(char **arg, char *commas);
bool check_rgb(char *rgb);
t_color	parse_color(char **rgb);

/*render*/
//draw
void render();
//pixel
void	put_pixel(t_color c, int x, int y);
//intersect
bool is_intersect(t_shape *shape, t_ray *ray, t_hit *inter);


/*entities*/
//ambient part
bool	parse_ambient(int counter[3], char **tmp, t_ambient *ambient);
//camera part
bool	parse_camera(int counter[3], char **tmp, t_camera *camera);
//light part
bool parse_light(int counter[3], char **arg, t_fclass *light);
t_light	*copy_light(t_light *light);
//shape part
t_shape	*copy_shape(t_shape *shape);
t_shape	*new_shape(void *data, t_shape_type type, int id);
//sphere part
bool	parse_sphere(char **tmp, t_fclass *fclass);
bool	inter_sphere(t_sphere *sphere, t_ray *ray, t_hit *inter);
//plane part
bool parse_plane(char **arg, t_fclass *fclass);
bool inter_plane(t_plane *plane, t_ray *ray, t_hit *inter);

/*vector part*/
//vector op basic
t_vector		vector_add(t_vector v1, t_vector v2);
t_vector		vector_subtract(t_vector v1, t_vector v2);
t_vector	vector_multiple(t_vector v1, double scalar);
//vector op plus
t_vector		vector_cross(t_vector v1, t_vector v2);
double			vector_dot(t_vector v1, t_vector v2);
t_vector		vector_normalize(t_vector a);
//vector tools
double			vector_len(t_vector a);
t_vector		parse_vector(char **strs);
t_vector	new_vector(double x, double y, double z);

/*tools*/
//equation
double solve(t_equation *equation);


//free the scene
void	delete_scene();

//show error message
void	error_exit(char *message);

//hook.c
int		ft_keypress(int keycode);
int		ft_quit();

//New function for fake class
t_fclass	*fclass_new(void *(*cpy)(void *), int (*cmp)(void *, void *),
	void (*print)(void *), void (*del)(void *));
void		push_to_fclass(t_fclass *fclass, void *element);


//debug part
void	print_shape(t_shape *shape);
void	print_light(t_light *light);

#endif