#include "libft.h"

//only for miniRT brightness value
char *ft_dtoa_simple(double n)
{
	int after_dot;
	char *res;
	char *tmp;

	res = ft_itoa((int)n);
	if (!res)
		return (NULL);
	after_dot = (int)((n - (int)n) * 10);
	if (after_dot < 0)
		after_dot = -after_dot;
	tmp = ft_itoa(after_dot);
	if (!tmp)
	{
		free(res);
		return (NULL);
	}
	res = ft_strjoin(res, ".");
	res = ft_strjoin(res, tmp);
	return (res);
}
