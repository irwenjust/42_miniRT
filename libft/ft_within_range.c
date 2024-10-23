/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_within_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:47:19 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 12:49:12 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_within_range(int num, int min, int max)
{
	if (num > max)
		return (max);
	else if (num < min)
		return (min);
	return (num);
}
