/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:17:27 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 11:11:49 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	compare_strs(int counter[3], char **tmp)
{
	if (!ft_strcmp("A", tmp[0]))
	{
		counter[0]++;
		return (true);  // check ambient later
	}
	else if (!ft_strcmp("C", tmp[0]))
	{
		counter[1]++;
		return (true);  // check camera later
	}
	else if (!ft_strcmp("L", tmp[0]))
	{
		counter[2]++;
		return (true);  // check light later
	}
	else if (!ft_strcmp("sp", tmp[0]))
		return (true);  // check sphere later
	else if (!ft_strcmp("pl", tmp[0]))
		return (true);  // check plane later
	else if (!ft_strcmp("cy", tmp[0]))
		return (true);  // check cylinder later
	else
		return (false);
}

void	parse_map(int counter[3])
{
	int		i;
	char	**tmp;
	
	i = -1;
	while (s()->map[++i])
	{
		tmp = ft_split(s()->map[i], ' ');
		if (!tmp)
			show_message("mistake happend when split file content");
		if (!compare_strs(counter, tmp))
		{
			free_matrix(tmp);
			show_message("mistake happend for file format");
		}
		free_matrix(tmp);
	}
}
