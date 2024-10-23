/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:35:34 by likong            #+#    #+#             */
/*   Updated: 2024/10/22 19:03:51 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_nof_validrows(char *file_name)
{
	int		fd;
	int		amount;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		show_message("cannot find/open this file");
	amount = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		//might need to add # also
		if (line[0] != '\n')
			amount++;
		free(line);
	}
	close(fd);
	return (amount);
}
