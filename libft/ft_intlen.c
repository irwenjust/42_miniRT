#include "libft.h"

int	ft_intlen(int n)
{
	int		size;
	long	num;

	size = 1;
	num = n;
	if (n < 0)
	{
		size++;
		num = -num;
	}
	while (num >= 10)
	{
		num /= 10;
		size++;
	}
	return (size);
}