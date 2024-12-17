#include "libft.h"
#include <math.h>

//only for miniRT brightness value
char *ft_dtoa_one(double n)
{
	int after_dot;
	char *res;
	char *tmp;
	char *after;

	after_dot = (int)round((n - (int)n) * 10);
	res = ft_itoa((int)(n));
	if (after_dot > 9)
	{
		after_dot = 0;
		res = ft_itoa((int)round(n));
	}
	if (!res)
		return (NULL);
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
