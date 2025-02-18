/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fclass_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:09:04 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:09:09 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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
