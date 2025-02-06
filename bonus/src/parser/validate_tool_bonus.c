#include "miniRT_bonus.h"

/*check syntax comma and is valid nbr or not*/
bool	check_number_arg(char **arg, char *isnbr)
{
	int		i;
	int     j;

	i = -1;
	while (arg[++i])
	{
		if (isnbr[i] == '1')
        {
            j = 0;
            while (arg[i][j])
            {
                if (ft_isdigit(arg[i][j]) || arg[i][j] == '.' || arg[i][j] == ',' || arg[i][j] == '-')
                    j++;
                else
                    return (ERROR("check nbr arg: not only nbr"), false);
            }
        }
	}
	return (true);
}

bool	check_rgb(char *rgb)
{
	int		i;
	bool	valid;
	char	**token;

	i = -1;
	valid = true;
	token = ft_split(rgb, ',');
	if (!token)
		return (ERROR("check rgb: split error"), false);
	if (ft_matrix_size(token) != 3)
		return (ERROR("check rgb: wrong number of rgb channel"), false);
	while (token[++i])
	{
		if (ft_atoi(token[i]) < 0 || ft_atoi(token[i]) > 255)
			valid = false;
		if (!valid)
			break ;
	}
	free_matrix(token);
	if (!valid)
		return (ERROR("check rgb: not int value/out of range, [0-255]"), false);
	return (valid);
}