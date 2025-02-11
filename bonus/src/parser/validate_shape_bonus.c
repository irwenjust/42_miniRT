#include "miniRT_bonus.h"

//[0]sp [1]Center [2]Diameter [3]Color [4]Ks [5]Shininess
//[6]checkerboard [7]texture [8]bump_texture 
//[9]Refractive_idx [10]transparency
bool validate_sphere(char **arg)
{
    //check arg size && nbr arg valid
    if (ft_matrix_size(arg) != 11)
		return (ERROR("sphere: wrong args format"), false);
    if (!check_arg_format(arg, "210100022000"))
		return (ERROR("sphere: number arg contains invalid char"), false);
    //check center [vector]
    //check diameter [double]
    if (ft_atod(arg[2]) * 0.5 < 1e-8)
		return (ERROR("sphere: wrong radius value"), false);
    //check color [0-255]
    if (!check_rgb(arg[3]))
		return (ERROR("sphere: wrong color value"), false);
    //check ks [0-1]
    if (ft_atod(arg[4]) < 0 || ft_atod(arg[4]) > 1)
		return (ERROR("sphere: wrong ks value"), false);
    //check shininess[1-128]
    if (ft_atod(arg[5]) < 1 || ft_atod(arg[5]) > 128)
		return (ERROR("sphere: wrong shininess value"), false);
    //check checkerboard[0/1]
    //check texture[path]
    //check bump_texture[path]
    //check refractive_idx [double]
    //check transparency [0-1]
    return (true);
}

//[0]pl [1]Center [2]normal [3]Color [4]Ks [5]Shininess
//[6]checkerboard [7]texture [8]bump_texture 
//[9]Refractive_idx [10]transparency
bool validate_plane(char **arg)
{
    //check arg size && nbr arg valid
    if (ft_matrix_size(arg) != 11)
		return (ERROR("plane: wrong args format"), false);
    if (!check_arg_format(arg, "211100022000"))
		return (ERROR("plane: number arg contains invalid char"), false);
    //check center [vector]
    //check normal [-1,1]
    //check color [0-255]
    if (!check_rgb(arg[3]))
		return (ERROR("plane: wrong color value"), false);
    //check ks [0-1]
    if (ft_atod(arg[4]) < 0 || ft_atod(arg[4]) > 1)
		return (ERROR("plane: wrong ks value"), false);
    //check shininess[1-128]
    if (ft_atod(arg[5]) < 1 || ft_atod(arg[5]) > 128)
		return (ERROR("plane: wrong shininess value"), false);
    //check checkerboard[0/1]
    //check texture[path]
    //check bump_texture[path]
    //check refractive_idx [double]
    //check transparency [0-1]
    return (true);
}

//[0]cy [1]Center [2]normal [3]Diameter [4]height [5]Color [6]Ks [7]Shininess
//[8]checkerboard [9]texture [10]bump_texture 
//[11]Refractive_idx [12]transparency
bool validate_cylinder(char **arg)
{
    //check arg size && nbr arg valid
    if (ft_matrix_size(arg) != 13)
		return (ERROR("cylinder: wrong args format"), false);
    if (!check_arg_format(arg, "21100100022000"))
		return (ERROR("cylinder: number arg contains invalid char"), false);
    //check center [vector]
    //check normal [-1.1]
    //check diameter [double]
    //check height [double]
    //check color [0-255]
    if (!check_rgb(arg[5]))
		return (ERROR("cylinder: wrong color value"), false);
    //check ks [0-1]
    if (ft_atod(arg[6]) < 0 || ft_atod(arg[6]) > 1)
		return (ERROR("cylinder: wrong ks value"), false);
    //check shininess[1-128]
    if (ft_atod(arg[7]) < 1 || ft_atod(arg[7]) > 128)
		return (ERROR("cylinder: wrong shininess value"), false);
    //check checkerboard[0/1]
    //check texture[path]
    //check bump_texture[path]
    //check refractive_idx [double]
    //check transparency [0-1]
    return (true);
}

//[0]co [1]Center [2]normal [3]Diameter [4]height [5]Color [6]Ks [7]Shininess
//[8]checkerboard [9]texture [10]bump_texture 
//[11]Refractive_idx [12]transparency
bool validate_cone(char **arg)
{
    //check arg size && nbr arg valid
    if (ft_matrix_size(arg) != 13)
		return (ERROR("cone: wrong args format"), false);
    if (!check_arg_format(arg, "21100100022000"))
		return (ERROR("cone: number arg contains invalid char"), false);
    //check center [vector]
    //check normal [-1.1]
    //check diameter [double]
    //check height [double]
    //check color [0-255]
    if (!check_rgb(arg[5]))
		return (ERROR("cone: wrong color value"), false);
    //check ks [0-1]
    if (ft_atod(arg[6]) < 0 || ft_atod(arg[6]) > 1)
		return (ERROR("cone: wrong ks value"), false);
    //check shininess[1-128]
    if (ft_atod(arg[7]) < 1 || ft_atod(arg[7]) > 128)
		return (ERROR("cone: wrong shininess value"), false);
    //check checkerboard[0/1]
    //check texture[path]
    //check bump_texture[path]
    //check refractive_idx [double]
    //check transparency [0-1]
    return (true);
}