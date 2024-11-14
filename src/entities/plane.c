#include "miniRT.h"

bool parse_plane(char **arg, t_fclass *fclass)
{
	t_shape *shape;
	t_plane plane;

	if (ft_matrix_size(arg) != 4 || !check_syntax(arg, "0111"))
		return (ERROR("plane: wrong args format"), false);
	
}