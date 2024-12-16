#include "libft.h"

//only for miniRT brightness value
char *ft_dtoa_simple(double n)
{
	int after_dot;
	char *res;
	char *tmp;
	char *after;

	res = ft_itoa((int)n);
	if (!res)
		return (NULL);
	after_dot = (int)((n - (int)n) * 10);
	if (after_dot < 0)
		after_dot = -after_dot;
	after = ft_itoa(after_dot);
	if (!after)
		return (free(res), NULL);
	tmp = ft_strjoin(res, ".");
	free(res);
	if (!tmp)
		return (free(after), NULL);
	res = ft_strjoin(tmp, after);
	free(tmp);
	free(after);
	return (res);
}
