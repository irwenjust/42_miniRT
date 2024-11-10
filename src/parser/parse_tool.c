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

static int	count_symbol(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
		if (*str++ == c)
			count++;
	return (count);
}

static bool check_double(char **double)
{
	int	i;
	char **nbr;
	int dot_nbr;

	i = -1;
	while (double[++i])
	{
		dot_nbr = count_symbol(double[i], '.');
		if (dot_nbr > 1)
			return (ERROR("check double: too many dots"), false);
		else if (dot_nbr == 0)
			nbr = double[i];
		else
		{
			nbr = ft_split(double[i], '.');
			if (!nbr)
				return (ERROR("check double: split error"), false);
		}
		if (!ft_isnum(nbr[0]) || (dot_nbr == 1 && !ft_isnum(nbr[1])))
			return (ERROR("check double: not number"), false);
	}
	return (true);

}

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
			valid = (count_symbol(arg[i], ',') == 2 && token_size == 3);
		else
			valid = (count_symbol(arg[i], ',') == 0 && token_size == 1);
		if (!check_double(token))
			valid = false;
		free_matrix(token);
		if (!valid)
			return (false);
	}
	return (true);
}

bool check_rgb(char *rgb)
{
	int i;
	bool valid;
	char **token;

	i = -1;
	valid = true;
	token = ft_split(rgb, ',');
	if (!token)
		return (ERROR("check rgb: split error"), false);
	while (token[++i])
	{
		if (!ft_isnum(token[i]))
			valid = false;
		if (ft_atoi(token[i] < 0 || ft_atoi(token[i] > 255)))
			valid = false;
		free_matrix(token);
		if (!valid)
			return (ERROR("check rgb: wrong rgb number"), false);
	}
	return (valid);
}
