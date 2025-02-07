/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:01:15 by likong            #+#    #+#             */
/*   Updated: 2024/08/29 12:03:20 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(char *str)
{
	int		i;
	bool	has_nbr;

	i = 0;
	has_nbr = false;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{		
		if (str[i] == '\n')
			break ;
		if (ft_isdigit(str[i]))
			has_nbr = true;
		else
			return (0);
		i++;
	}
	if (!has_nbr)
		return (0);
	return (1);
}
