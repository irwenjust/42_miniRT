/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:55:29 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/17 11:44:09 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static int	count_symbol(char *str, char c)
// {
// 	int	count;

// 	count = 0;
// 	while (*str)
// 		if (*str++ == c)
// 			count++;
// 	return (count);
// }

// static bool	check_nbr(char **nbr)
// {
// 	int		i;
// 	char	**token;
// 	int		dot_nbr;
// 	bool	valid;

// 	i = -1;
// 	valid = true;
// 	while (nbr[++i])
// 	{
// 		dot_nbr = count_symbol(nbr[i], '.');
// 		if (dot_nbr > 1)
// 			return (error("check nbr: too many dots"), false);
// 		else
// 		{
// 			token = ft_split(nbr[i], '.');
// 			if (!token)
// 				return (error("check nbr: split error"), false);
// 		}
// 		if (!ft_isnum(token[0]) || (dot_nbr == 1 && !ft_isnum(token[1])))
// 			valid = false;
// 		free_matrix(token);
// 		if (!valid)
// 			return (error("check nbr: not number"), false);
// 	}
// 	return (true);
// }

// /*check syntax comma and is valid nbr or not*/
// bool	check_syntax(char **arg, char *commas)
// {
// 	int		i;
// 	char	**token;
// 	int		token_size;
// 	bool	valid;

// 	i = -1;
// 	valid = true;
// 	while (arg[++i])
// 	{
// 		token = ft_split(arg[i], ',');
// 		if (!token)
// 			return (error("check syntax: split error"), false);
// 		token_size = ft_matrix_size(token);
// 		if (commas[i] == HAS_COMMA)
// 			valid = (count_symbol(arg[i], ',') == 2 && token_size == 3);
// 		else
// 			valid = (count_symbol(arg[i], ',') == 0 && token_size == 1);
// 		// if ((i > 0 && !check_nbr(token)) || token[token_size - 1][0] == '\n')
// 		// 	valid = false;
// 		free_matrix(token);
// 		if (!valid)
// 			return (false);
// 	}
// 	return (true);
// }

bool	check_rgb(char *rgb)
{
	int		i;
	bool	valid;
	char	**token;

	i = -1;
	valid = true;
	token = ft_split(rgb, ',');
	if (!token)
		return (error("check rgb: split error"), false);
	while (token[++i])
	{
		if (!ft_isnum(token[i]))
			valid = false;
		if (ft_atoi(token[i]) < 0 || ft_atoi(token[i]) > 255)
			valid = false;
		if (!valid)
			break ;
	}
	free_matrix(token);
	if (!valid)
		return (error("check rgb: wrong rgb number"), false);
	return (valid);
}

t_color	parse_color(char **rgb)
{
	return ((t_color){
		.red = ft_within_range(ft_atoi(rgb[0]), 0, 255),
		.green = ft_within_range(ft_atoi(rgb[1]), 0, 255),
		.blue = ft_within_range(ft_atoi(rgb[2]), 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}
