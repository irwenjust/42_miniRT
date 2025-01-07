/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:22:53 by likong            #+#    #+#             */
/*   Updated: 2025/01/07 11:57:13 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_bvh	*build_bvh(t_shape **shapes, int amount)
{
	t_bvh	*res;
	int		max_axis;
	int		split_index;

	res = ft_calloc(1, sizeof(t_bvh));
	if (!res)
		return (NULL);
	res->id = s()->bvh_level++;
	if (amount == 1)
	{
		res->box = shapes[0]->box;
		res->shapes = shapes[0];
		return (res);
	}
	res->box = generate_box(shapes, amount);
	max_axis = find_max_axis(res->box);
	split_index = split_box(max_axis, shapes, amount);
	if (split_index == 0 || split_index == amount)
		split_index = amount * 0.5;
	res->left = build_bvh(shapes, split_index);
	res->right = build_bvh(shapes + split_index, amount - split_index);
	return (res);
}

void	free_bvh(t_bvh **bvh)
{
	if (!bvh || !*bvh)
		return ;
	free_bvh(&(*bvh)->left);
	free_bvh(&(*bvh)->right);
	free(*bvh);
	*bvh = NULL;
}

t_bvh	*init_bvh(void)
{
	t_bvh	*res;
	t_shape	**tmp;

	s()->bvh_level = 0;
	if (!s()->shapes)
		return (NULL);
	tmp = shapes_to_arr((t_shape **)s()->shapes->array);
	if (!tmp)
		return (NULL);
	res = build_bvh(tmp, s()->shapes->size);
	free (tmp);
	return (res);
}

void	rebuild_bvh(void)
{
	if (s()->bvh)
		free_bvh(&s()->bvh);
	if (!s()->shapes)
		return ;
	s()->bvh = init_bvh();
	if (!s()->bvh)
		error_exit("Cannot initialize bvh tree");
}
