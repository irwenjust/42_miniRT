/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:24:56 by likong            #+#    #+#             */
/*   Updated: 2025/01/13 12:25:32 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_fclass(void)
{
	(s()->light) = fclass_new((void *)&copy_light, NULL, &free,
			(void *)&print_light);
	(s()->ori_light) = fclass_new((void *)&copy_light, NULL, &free,
			(void *)&print_light);
	(s()->shapes) = fclass_new((void *)&copy_shape, NULL, &free,
			(void *)&print_shape);
	(s()->ori_shapes) = fclass_new((void *)&copy_shape, NULL, &free,
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

void	init_viewport(void)
{
	s()->view_w = tan(RADIAN(s()->camera.fov * 0.5));
	s()->view_h = s()->view_w * SCALE;
	(s()->normal_w) = vector_normalize(
			vector_cross(s()->camera.normal, UPVECTOR));
	(s()->normal_h) = vector_normalize(
			vector_cross(s()->camera.normal, s()->normal_w));
	(s()->normal_w) = vector_normalize(
			vector_cross(s()->camera.normal, s()->normal_h));
}

static void	init_windows(void)
{
	(s()->win.mlx) = mlx_init();
	if (!s()->win.mlx)
		error_exit("error happend when create MLX42");
	(s()->win.disp) = mlx_new_window(s()->win.mlx, WIDTH, HEIGHT, "miniRT");
	if (!s()->win.disp)
		error_exit("error happend when create MLX42 windows");
	s()->win.width = WIDTH;
	s()->win.height = HEIGHT;
	(s()->win.img) = mlx_new_image(s()->win.mlx, s()->win.width,
			s()->win.height);
	if (!s()->win.img)
		error_exit("error happend when create MLX42 image");
	(s()->win.menu) = mlx_new_image(s()->win.mlx, WIDTH, (HEIGHT * 0.12));
	if (!s()->win.menu)
		error_exit("error happend when initial MLX42 menu");
	(s()->win.addr) = mlx_get_data_addr(s()->win.img, &s()->win.bpp,
			&s()->win.line_len, &s()->win.endian);
	if (!s()->win.addr)
		error_exit("error happend when initial MLX42 image address");
}

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
	rebuild_bvh();
	backup_scene();
}
