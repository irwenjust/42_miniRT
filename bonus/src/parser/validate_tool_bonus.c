#include "miniRT_bonus.h"

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
		return (ERROR("check rgb: not an int/out of range, [0-255]"), false);
	return (valid);
}
