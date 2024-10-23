/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:24:56 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 09:13:27 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (counter[0] == 0)
		show_message("No ambient in the scene");
	else if (counter[1] == 0)
		show_message("No camera in the scene");
	else if (counter[2] == 0)
		show_message("No light in the scene");
	else if (counter[0] > 1 || counter[1] > 1 || counter[2] > 1)
		show_message("too many ambient/camera/light in the scene");
}

// void	init_point(void)
// {
// 	ft_bzero(p(), sizeof(t_point));
// 	p()->x = 4.3;
// 	p()->y = -4.2;
// 	p()->z = 3.1;
// 	p()->type = 1;
// }

// void	init_vector(void)
// {
// 	ft_bzero(v(), sizeof(t_vector));
// 	v()->x = 4.3;
// 	v()->y = -4.2;
// 	v()->z = 3.1;
// 	v()->type = 0;
// }
