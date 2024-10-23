#ifndef MINIRT_H
# define MINIRT_H

# define SUCCESS 0
# define FAIL_STD 1

# define AMBIENT 0
# define CAMERA 1
# define LIGHT 2

/*
stdio: printf
fcntl: O_RDONLY
stdlib: malloc, free
*/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>

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

//shape part
t_shape	*copy_shape(t_shape *shape);
void	print_shape(t_shape *shape);

//light part
t_light	*copy_light(t_light *light);
void	print_light(t_light *light);

//file part
int		get_nof_validrows(char *file_name);

//map part
void	parse_map(int counter[3]);

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