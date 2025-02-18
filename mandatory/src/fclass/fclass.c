/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fclass.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:30:41 by likong            #+#    #+#             */
/*   Updated: 2024/12/31 13:22:21 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	*fclass_index(t_fclass *fclass, int i)
{
	if (fclass && i < fclass->size)
		return (fclass->array[i]);
	return (NULL);
}

void	push_to_fclass(t_fclass *fclass, void *element)
{
	void	**tmp;

	if (!fclass)
		return ;
	tmp = append_matrix(fclass->array, element, fclass->cpy);
	free_matrix((char **)fclass->array);
	fclass->array = tmp;
	fclass->size++;
}

t_fclass	*fclass_new(void *(*cpy)(void *), int (*cmp)(void *, void *),
	void (*del)(void *), void (*print)(void *))
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
