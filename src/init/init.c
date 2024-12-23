/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:24:56 by likong            #+#    #+#             */
/*   Updated: 2024/11/27 13:57:42 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_fclass()
{
	s()->light = fclass_new((void *)&copy_light, NULL, &free,
		(void *)&print_light);
	s()->ori_light = fclass_new((void *)&copy_light, NULL, &free,
		(void *)&print_light);
	//print????
	s()->shapes = fclass_new((void *)&copy_shape, NULL, &free,
		(void *)&print_shape);
	s()->ori_shapes = fclass_new((void *)&copy_shape, NULL, &free,
		(void *)&print_shape);

}

static void	init_args(char *file_name)
{
	int		i;
	int		fd;
	char	*line;
	
	s()->args = ft_matrix_new(get_nof_validrows(file_name));
	if (!s()->args)
		error_exit("some mistake happend when allocate for read map");
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_exit("cannot find/open this file");
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strchr("\n#", line[0]))
			s()->args[i++] = line;
		else
			free(line);
	}
	close (fd);
}

static void	init_viewport()
{
	s()->view_w = tan(RADIAN(s()->camera.fov * 0.5));
	s()->view_h = s()->view_w * SCALE;
	s()->normal_w = vector_normalize(vector_cross(s()->camera.normal, UPVECTOR));
	s()->normal_h = vector_normalize(vector_cross(s()->camera.normal, s()->normal_w));
	s()->normal_w = vector_normalize(vector_cross(s()->camera.normal, s()->normal_h));
}

static void	init_windows()
{
	s()->win.mlx = mlx_init();
	if (!s()->win.mlx)
		error_exit("error happend when create MLX42");
	s()->win.width = WIDTH;
	s()->win.height = HEIGHT;
	s()->win.disp = mlx_new_window(s()->win.mlx, WIDTH, HEIGHT, "miniRT");
	if (!s()->win.disp)
		error_exit("error happend when create MLX42 windows");
	s()->win.img = mlx_new_image(s()->win.mlx, s()->win.width, s()->win.height);
	if (!s()->win.img)
		error_exit("error happend when create MLX42 image");
	s()->win.addr = mlx_get_data_addr(s()->win.img, &s()->win.bpp, 
		&s()->win.line_len, &s()->win.endian);
	if (!s()->win.addr)
		error_exit("error happend when initial MLX42 image address");
	s()->win.menu = mlx_new_image(s()->win.mlx, WIDTH, (HEIGHT * 0.12));
	if (!s()->win.menu)
		error_exit("error happend when initial MLX42 menu");
}

// void printTree(t_bvh *root, int space) {
//     // Base case
//     if (root == NULL)
//         return;

//     // Increase distance between levels
//     space += 5;

//     // Print right subtree first (for visual alignment)
//     printTree(root->right, space);

//     // Print the current node after space
//     printf("\n");
//     for (int i = 5; i < space; i++) {
//         printf(" "); // Print space for alignment
//     }
//     printf("%d\n", root->id);

//     // Print left subtree
//     printTree(root->left, space);
// }

void	init_scene(char *file_name)
{
	ft_bzero(s(), sizeof(t_scene));
	if (!validate_filename(file_name))
		error_exit("the file should end in .rt");
	init_fclass();
	init_args(file_name);
	if (ft_matrix_size(s()->args) == 0)
		error_exit("the file is empty");
	parse_args();
	
	
	
	init_viewport();
	init_windows();
	ft_bzero(&(s()->keys), sizeof(t_key));
	s()->keys.cur_keycode = -1;
	s()->menu = VIEW;
	gettimeofday(&s()->last_frame_time, NULL);
	// int i = -1;
	// t_shape *shape;
	// while (++i < s()->shapes->size)
	// {
	// 	if (i > 0)
	// 	{
	// 		shape = s()->shapes->array[i];
	// 		// print_shape(shape);
	// 		printf("before re build min: (%f, %f, %f), max: (%f, %f, %f)\n",
	// 		shape->data.cylinder.box.min.x, shape->data.cylinder.box.min.y, shape->data.cylinder.box.min.z,
	// 		shape->data.cylinder.box.max.x, shape->data.cylinder.box.max.y, shape->data.cylinder.box.max.z);
	// 	}
	// }
	rebuild_bvh();
	// printf("after rebuild ");
	// print_box(s()->bvh->box);
	backup_scene();
	
	// printTree(s()->bvh, 0);
}
