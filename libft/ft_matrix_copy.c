/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:41:11 by likong            #+#    #+#             */
/*   Updated: 2024/10/24 10:44:56 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*copy_matrix(void *matrix, void *(*copy)(void *))
{
	void	**res;
	size_t	i;

	res = ft_calloc(ft_matrix_size(matrix) + 1, sizeof(void *));
	if (!res)
		return (NULL);
	i = -1;
	while (((void **)matrix)[++i])
	{
		if (copy)
			res[i] = (*copy)(((void **)matrix)[i]);
		else
			res[i] = ((void **)matrix)[i];
	}
	return (res);
}
