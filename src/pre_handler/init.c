/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:24:56 by likong            #+#    #+#             */
/*   Updated: 2024/10/28 19:12:49 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_windows()
{
	// s()->win.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	// if (!s()->win.mlx)
	// 	show_message("error happend when create MLX42");
	s()->win.mlx = mlx_init();
	if (!s()->win.mlx)
		show_message("error happend when create MLX42");
	s()->win.width = WIDTH;
	s()->win.height = HEIGHT;
	s()->win.disp = mlx_new_window(s()->win.mlx, WIDTH, HEIGHT, "miniRT");
	if (!s()->win.disp)
		show_message("error happend when create MLX42 windows");
	s()->win.img = mlx_new_image(s()->win.mlx, s()->win.width, s()->win.height);
	if (!s()->win.img)
		show_message("error happend when create MLX42 image");
	s()->win.addr = mlx_get_data_addr(s()->win.img, &s()->win.bpp, 
		&s()->win.line_len, &s()->win.endian);
	if (!s()->win.addr)
		show_message("error happend when initial MLX42 image address");
}

static void	init_map(char *file_name)
{
	int		i;
	int		fd;
	char	*line;
	
	s()->map = ft_matrix_new(get_nof_validrows(file_name));
	if (!s()->map)
		show_message("some mistake happend when allocate for read map");
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		show_message("cannot find/open this file");
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strchr("\n#", line[0]))
			s()->map[i++] = line;
		else
			free(line);
	}
	close (fd);
}

static void	init_fclass()
{
	s()->light = fclass_new((void *)&copy_light, NULL, &free,
		(void *)&print_light);
	s()->shapes = fclass_new((void *)&copy_shape, NULL, &free,
		(void *)&print_shape);
}

void	init_scene(char *file_name)
{
	int	counter[3];

	ft_bzero(s(), sizeof(t_scene));
	ft_bzero(counter, 3 * sizeof(int));
	if (!validate_filename(file_name))
		show_message("the file should end in .rt");
	init_fclass();
	init_map(file_name);
	if (ft_matrix_size(s()->map) == 0)
		show_message("the file is empty");
	parse_map(counter);
	check_counter(counter);
	init_viewport();
	init_windows();
	draw_image();
	mlx_hook(s()->win.disp, DestroyNotify, StructureNotifyMask, quit, NULL); // need to adjust later maybe
	mlx_loop(s()->win.mlx);
}
