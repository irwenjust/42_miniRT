#include "miniRT_bonus.h"

//[0]A [1]brightness [2]color
bool validate_ambient(char **arg)
{
	//check arg size && nbr arg valid
    if (ft_matrix_size(arg) != 3)
		return (ERROR("ambient: wrong number of args, [3]"), false);
	if (!check_arg_format(arg, "201"))
		return (ERROR("ambient: invalid number arg format"), false);
    //check brightness double [0-1]
	if (ft_atod(arg[1]) < 0.0 || ft_atod(arg[1]) > 1.0)
		return (ERROR("ambient: wrong brightness ratio range, [0-1]"), false);
    //check color [0-255]
	if (!check_rgb(arg[2]))
		return (ERROR("ambient: wrong color arg"), false);
	return (true);
}

//[0]C [1]Center [2]normal [3]FOV
bool validate_camera(char **arg)
{
    //check arg size && nbr arg valid
    if (ft_matrix_size(arg) != 4)
		return (ERROR("camera: wrong number of args, [4]"), false);
	if (!check_arg_format(arg, "2110"))
		return (ERROR("camera: number arg contains invalid char"), false);
    //check center [vector]
    //check normal [-1,1] 数字越界检查可能在arg format里，normal长度检查在parse之后更方便
    //check fov [0-180 !=]
	if (ft_atoi(arg[3]) < 0 || ft_atoi(arg[3]) > 180)
		return (ERROR("camera: FOV is out of range, [0-180,!=]"), false);
	return (true);
}

//[0]L [1]center [2]brightness [3]color
bool validate_light(char **arg)
{
    //check arg size && nbr arg valid
    if (ft_matrix_size(arg) != 4)
		return (ERROR("light: wrong args format"), false);
	if (!check_arg_format(arg, "2101"))
		return (ERROR("light: number arg contains invalid char"), false);
    //check center [vector]
    //check brightness double [0-1]
    if (ft_atod(arg[2]) < 0.0 || ft_atod(arg[2]) > 1.0)
		return (ERROR("light: wrong brightness ratio range"), false);
    //check color [0-255]
    if (!check_rgb(arg[3]))
		return (ERROR("light: wrong color value"), false);
	return (true);
}