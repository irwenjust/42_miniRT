/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:25:28 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 20:14:59 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define SUCCESS 0
# define FAIL_STD 1

# define AMBIENT 0
# define CAMERA 1
# define LIGHT 2

# define R 0
# define G 1
# define B 2

# define X 0
# define Y 1
# define Z 2

# define ERROR(s) printf("Error: %s\n", s)

/*
stdio: printf
fcntl: O_RDONLY
stdlib: malloc, free
*/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "libft.h"
#include "structure.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/get_next_line/get_next_line.h"

//
t_scene	*s(void);

//free the scene
void	delete_scene();

//show error message
void	show_message(char *message);

//initial part
void	init_scene(char *file_name);

//validate
bool	validate_filename(char *f_name);

//New function for fake class
t_fclass	*fclass_new(void *(*cpy)(void *), int (*cmp)(void *, void *),
	void (*print)(void *), void (*del)(void *));
void		push_to_fclass(t_fclass *fclass, void *element);

//shape part
t_shape	*copy_shape(t_shape *shape);
void	print_shape(t_shape *shape);
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

//vector part
t_vector		save_vector(char **strs);
t_vector		normalize_vector(t_vector a);
double			vector_len(t_vector a);

//sphere part
bool	save_sphere(char **tmp, t_fclass *fclass);


// typedef struct s_point
// {
// 	double	x;
// 	double	y;
// 	double	z;
// 	int		type;
// }	t_point;

// typedef struct s_vector
// {
// 	double	x;
// 	double	y;
// 	double	z;
// 	int		type;
// }	t_vector;

// t_point		*p(void);
// t_vector	*v(void);

// void		init_point(void);
// void		init_vector(void);

#endif