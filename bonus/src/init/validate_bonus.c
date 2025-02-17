/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:09:58 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/17 13:37:41 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

bool	validate_filename(char *f_name)
{
	if (ft_strncmp(f_name + ft_strlen(f_name) - 3, ".rt", 3))
		return (false);
	return (true);
}

int	get_nof_validrows(char *file_name)
{
	int		fd;
	int		amount;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_exit("cannot find/open this file");
	amount = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			amount++;
		free(line);
	}
	close(fd);
	return (amount);
}
