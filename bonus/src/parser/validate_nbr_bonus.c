#include "miniRT_bonus.h"

static int	count_symbol(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
		if (*str++ == c)
			count++;
	return (count);
}

static bool	check_comma(char **token, int comma_nbr, int arg_type)
{
	int		token_size;
	bool	valid;

	token_size = ft_matrix_size(token);
	if (arg_type == HAS_COMMA)
		valid = (comma_nbr == 2 && token_size == 3);
	else
		valid = (comma_nbr == 0 && token_size == 1);
	return (valid);
}

static bool	check_nbr(char **nbr)
{
	int	i;
	char	**token;
	int		dot_nbr;
	bool	valid;

	i = -1;
	valid = true;
	while (nbr[++i])
	{
		dot_nbr = count_symbol(nbr[i], '.');
		if (dot_nbr > 1)
			return (ERROR("check arg format: too many dots in nbr"), false);
		token = ft_split(nbr[i], '.');
		if (!token)
			return (ERROR("check arg format: split error for dot"), false);
		if (!ft_isnum(token[0]) || (dot_nbr == 1 && !ft_isnum(token[1])))
			valid = false;
        //may add check nbr overflow here later
		free_matrix(token);
		if (!valid)
			return (ERROR("check arg format: invalid number"), false);
	}
	return (true);
}

/*check syntax comma and is valid nbr or not*/
bool	check_arg_format(char **arg, char *arg_type)
{
	int	i;
	char	**token;
	int		comma_nbr;
	bool	valid;

	i = -1;
	valid = true;
	while (arg[++i])
	{
		if (arg_type[i] == NOT_NBR)
			continue ;
		comma_nbr = count_symbol(arg[i], ',');
		if (comma_nbr != 0 && comma_nbr != 2)
			return (ERROR("check arg format: wrong comma nbr"), false);
		token = ft_split(arg[i], ',');
		if (!token)
			return (ERROR("check arg format: split error for comma"), false);
		if (!check_comma(token, comma_nbr, arg_type[i]) || !check_nbr(token))
			valid = false;
		free_matrix(token);
		if (!valid)
			return (false);
	}
	return (true);
}
