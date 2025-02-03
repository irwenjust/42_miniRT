/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:27:23 by likong            #+#    #+#             */
/*   Updated: 2025/01/31 14:52:46 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

double	ft_rand(void)
{
	return (rand() / (double) RAND_MAX + 1.0);
}

t_shape	**shapes_to_arr(t_shape **shapes)
{
	t_shape	**res;
	int		i;

	i = -1;
	res = ft_calloc(s()->shapes->size, sizeof(t_shape *));
	while (shapes[++i])
		res[i] = shapes[i];
	return (res);
}

void	ft_swap_d(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char	*save_str_without_newline(char *str)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*res;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	res = (char *)malloc(len + 1);
	if (!res)
	{
		free(str);
		return (NULL);
	}
	j = 0;
	i = -1;
	while (++i < len)
	{
		if (str[i] != '\n' && str[i] != '\0')
			res[j++] = str[i];
	}
	res[j] = '\0';
	free(str);
	str = NULL;
	return (res);
}

t_hit	init_hit(void)
{
	t_hit	hit;
	
	ft_bzero(&hit, sizeof(t_hit));
	hit.color = BLACK;
	hit.distance = INFINITY;
	hit.shape = NULL;

	return (hit);
}

void	check_hit(t_hit *hit)
{
	hit->hit_point = vector_add(hit->ray.start, vector_scale(hit->ray.normal, hit->distance));
	check_hit_normal(hit);
	find_uv(hit);
}
