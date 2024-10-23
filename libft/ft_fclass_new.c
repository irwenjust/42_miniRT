/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fclass_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:30:41 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 09:47:44 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_fclass	*fclass_new(void *(*cpy)(void *), int (*cmp)(void *, void *),
	void (*print)(void *), void (*del)(void *))
{
	t_fclass	*res;

	res = ft_calloc(1, sizeof(t_fclass));
	if (!res)
		return (NULL);
	res->array = ft_calloc(1, sizeof(void *));
	if (!res->array)
	{
		free(res);
		return (NULL);
	}
	res->cpy = cpy;
	res->cmp = cmp;
	res->print = print;
	res->del = del;
	return (res);
}
