/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:05:26 by likong            #+#    #+#             */
/*   Updated: 2025/01/15 12:41:11 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*append_matrix(void *matrix, void *data, void *(*copy)(void *))
{
	void	**res;
	size_t	i;

	i = -1;
	res = ft_calloc(ft_matrix_size(matrix) + 2, sizeof(void *));
	if (!res)
		return (NULL);
	while (((void **)matrix)[++i])
	{
		if (copy)
			res[i] = (*copy)(((void **)matrix)[i]);
		else
			res[i] = ((void **)matrix)[i];
	}
	res[i] = data;
	return (res);
}
