/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:55:29 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/08 14:57:19 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	count_comma(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
		if (*str++ == c)
			count++;
	return (count);
}

//static bool check_double()
//{


//}

bool	check_syntax(char **arg, char *commas)
{
	int		i;
	char	**token;
	int		token_size;
	bool	valid;

	i = -1;
	valid = true;
	while (arg[++i])
	{
		token = ft_split(arg[i], ',');
		if (!token)
			return (ERROR("check syntax: split error"), false);
		token_size = ft_matrix_size(token);
		if (commas[i] == HAS_COMMA)
			valid = (count_comma(arg[i], ',') == 2 && token_size == 3);
		else
			valid = (count_comma(arg[i], ',') == 0 && token_size == 1);
		//if (!check_double(token))
		//	valid = false;
		free_matrix(token);
		if (!valid)
			return (false);
	}
	return (true);
}

//bool check_rgb()
//{

//}
