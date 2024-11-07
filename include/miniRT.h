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

#include "libft.h"
#include "structure.h"
#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include "../libft/get_next_line/get_next_line.h"

//
t_scene	*s(void);

//free the scene
void	delete_scene();

//show error message
void	show_message(char *message);
int		quit();
int		keypress(int keycode);


//check part
void	check_counter(int counter[3]);

//initial part
void	init_scene(char *file_name);
void	init_viewport();

//validate
bool	validate_filename(char *f_name);

//New function for fake class
t_fclass	*fclass_new(void *(*cpy)(void *), int (*cmp)(void *, void *),
	void (*print)(void *), void (*del)(void *));
void		push_to_fclass(t_fclass *fclass, void *element);

//shape part
t_shape	*copy_shape(t_shape *shape);
t_shape	*shape_new(void *data, t_shape_type type, int id);

//light part
t_light	*copy_light(t_light *light);
void	print_light(t_light *light);

//file part
int		get_nof_validrows(char *file_name);

//map part
void	parse_map(int counter[3]);

//ambient part
bool	save_ambient(int counter[3], char **tmp, t_ambient *ambient);

//camera part
bool	save_camera(int counter[3], char **tmp, t_camera *camera);

//color part
t_color	save_color(char **rgb);
void	draw_image();

//vector part
t_vector		save_vector(char **strs);
t_vector		normalize_vector(t_vector a);
double			vector_len(t_vector a);
t_vector		vector_cross(t_vector v1, t_vector v2);
double			vector_dot(t_vector v1, t_vector v2);

//sphere part
bool	save_sphere(char **tmp, t_fclass *fclass);

//debug part
void	print_shape(t_shape *shape);


#endif