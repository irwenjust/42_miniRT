/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:28:15 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 09:13:39 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_matrix_new(size_t lines)
{
	void	*res;

	res = ft_calloc(lines + 1, sizeof(char *));
	if (!res)
		return (NULL);
	return (res);
}
