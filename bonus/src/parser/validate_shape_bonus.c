/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_shape_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:13:54 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:15:31 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

//[0]sp [1]Center [2]Diameter [3]Color [4]Ks [5]Shininess
//[6]checkerboard [7]texture [8]bump_texture 
//[9]Refractive_idx [10]transparency
bool	validate_sphere(char **arg)
{
	if (ft_matrix_size(arg) != 11)
		return (ERROR("sphere: wrong args format"), false);
	if (!check_arg_format(arg, "210100022000"))
		return (ERROR("sphere: number arg contains invalid char"), false);
	if (ft_atod(arg[2]) * 0.5 < 1e-8)
		return (ERROR("sphere: wrong radius value"), false);
	if (!check_rgb(arg[3]))
		return (ERROR("sphere: wrong color value"), false);
	if (ft_atod(arg[4]) < 0 || ft_atod(arg[4]) > 1)
		return (ERROR("sphere: wrong ks value"), false);
	if (!ft_isnum(arg[5]) || ft_atod(arg[5]) < 1 || ft_atod(arg[5]) > 128)
		return (ERROR("sphere: wrong shininess value"), false);
	if (ft_atod(arg[6]) != 0 && ft_atod(arg[6]) != 1)
		return (ERROR("sphere: wrong checkerboard value"), false);
	if (ft_atod(arg[9]) <= 0 || ft_atod(arg[9]) > INT_MAX)
		return (ERROR("sphere: wrong refractive index"), false);
	if (ft_atod(arg[10]) != 0 && ft_atod(arg[10]) != 1)
		return (ERROR("sphere: wrong transparency value"), false);
	return (true);
}

//[0]pl [1]Center [2]normal [3]Color [4]Ks [5]Shininess
//[6]checkerboard [7]texture [8]bump_texture 
//[9]Refractive_idx [10]transparency
bool	validate_plane(char **arg)
{
	if (ft_matrix_size(arg) != 11)
		return (ERROR("plane: wrong args format"), false);
	if (!check_arg_format(arg, "211100022000"))
		return (ERROR("plane: number arg contains invalid char"), false);
	if (!check_rgb(arg[3]))
		return (ERROR("plane: wrong color value"), false);
	if (ft_atod(arg[4]) < 0 || ft_atod(arg[4]) > 1)
		return (ERROR("plane: wrong ks value"), false);
	if (!ft_isnum(arg[5]) || ft_atod(arg[5]) < 1 || ft_atod(arg[5]) > 128)
		return (ERROR("plane: wrong shininess value"), false);
	if (ft_atod(arg[6]) != 0 && ft_atod(arg[6]) != 1)
		return (ERROR("plane: wrong checkerboard value"), false);
	if (ft_atod(arg[9]) <= 0 || ft_atod(arg[9]) > INT_MAX)
		return (ERROR("plane: wrong refractive index"), false);
	if (ft_atod(arg[10]) != 0 && ft_atod(arg[10]) != 1)
		return (ERROR("plane: wrong transparency value"), false);
	return (true);
}

//[0]cy [1]Center [2]normal [3]Diameter [4]height [5]Color [6]Ks [7]Shininess
//[8]checkerboard [9]texture [10]bump_texture 
//[11]Refractive_idx [12]transparency
bool	validate_cylinder(char **arg)
{
	if (ft_matrix_size(arg) != 13)
		return (ERROR("cylinder: wrong args format"), false);
	if (!check_arg_format(arg, "21100100022000"))
		return (ERROR("cylinder: number arg contains invalid char"), false);
	if (ft_atod(arg[3]) * 0.5 < 1e-8)
		return (ERROR("cylinder: wrong radius value"), false);
	if (ft_atod(arg[4]) < 1e-8)
		return (ERROR("cylinder: wrong height value"), false);
	if (!check_rgb(arg[5]))
		return (ERROR("cylinder: wrong color value"), false);
	if (ft_atod(arg[6]) < 0 || ft_atod(arg[6]) > 1)
		return (ERROR("cylinder: wrong ks value"), false);
	if (!ft_isnum(arg[7]) || ft_atod(arg[7]) < 1 || ft_atod(arg[7]) > 128)
		return (ERROR("cylinder: wrong shininess value"), false);
	if (ft_atod(arg[8]) != 0 && ft_atod(arg[8]) != 1)
		return (ERROR("cylinder: wrong checkerboard value"), false);
	if (ft_atod(arg[11]) <= 0 || ft_atod(arg[1]) > INT_MAX)
		return (ERROR("cylinder: wrong refractive index"), false);
	if (ft_atod(arg[12]) != 0 && ft_atod(arg[12]) != 1)
		return (ERROR("cylinder: wrong transparency value"), false);
	return (true);
}

//[0]co [1]Center [2]normal [3]Diameter [4]height [5]Color [6]Ks [7]Shininess
//[8]checkerboard [9]texture [10]bump_texture 
//[11]Refractive_idx [12]transparency
bool	validate_cone(char **arg)
{
	if (ft_matrix_size(arg) != 13)
		return (ERROR("cone: wrong args format"), false);
	if (!check_arg_format(arg, "21100100022000"))
		return (ERROR("cone: number arg contains invalid char"), false);
	if (ft_atod(arg[3]) * 0.5 < 1e-8)
		return (ERROR("cone: wrong radius value"), false);
	if (ft_atod(arg[4]) < 1e-8)
		return (ERROR("cone: wrong height value"), false);
	if (!check_rgb(arg[5]))
		return (ERROR("cone: wrong color value"), false);
	if (ft_atod(arg[6]) < 0 || ft_atod(arg[6]) > 1)
		return (ERROR("cone: wrong ks value"), false);
	if (!ft_isnum(arg[7]) || ft_atod(arg[7]) < 1 || ft_atod(arg[7]) > 128)
		return (ERROR("cone: wrong shininess value"), false);
	if (ft_atod(arg[8]) != 0 && ft_atod(arg[8]) != 1)
		return (ERROR("cone: wrong checkerboard value"), false);
	if (ft_atod(arg[11]) <= 0 || ft_atod(arg[11]) > INT_MAX)
		return (ERROR("cone: wrong refractive index"), false);
	if (ft_atod(arg[12]) != 0 && ft_atod(arg[12]) != 1)
		return (ERROR("cone: wrong transparency value"), false);
	return (true);
}
