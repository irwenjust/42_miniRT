

#include "miniRT_bonus.h"

t_color	parse_color(char **rgb)
{
	return ((t_color){
		.red = ft_within_range(ft_atoi(rgb[0]), 0, 255),
		.green = ft_within_range(ft_atoi(rgb[1]), 0, 255),
		.blue = ft_within_range(ft_atoi(rgb[2]), 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}
