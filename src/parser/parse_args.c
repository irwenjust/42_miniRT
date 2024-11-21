/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:17:27 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 20:18:10 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*check each line of args if valid or not*/
static bool	parse_line(int counter[3], char **arg)
{
	if (!ft_strcmp("A", arg[0]))
		return (parse_ambient(counter, arg, &s()->ambient));
	else if (!ft_strcmp("C", arg[0]))
		return (parse_camera(counter, arg, &s()->camera));
	else if (!ft_strcmp("L", arg[0]))
		return (parse_light(counter, arg, s()->light));
	else if (!ft_strcmp("sp", arg[0]))
		return (parse_sphere(arg, s()->shapes));
	else if (!ft_strcmp("pl", arg[0]))
		return (parse_plane(arg, s()->shapes));
	else if (!ft_strcmp("cy", arg[0]))
		return (parse_cylinder(arg, s()->shapes));
	else
		return (false);
}

static void	check_counter(int counter[3])
{
	if (counter[0] == 0)
		error_exit("No ambient in the scene");
	else if (counter[1] == 0)
		error_exit("No camera in the scene");
	else if (counter[2] == 0)
		error_exit("No light in the scene");
	else if (counter[0] > 1 || counter[1] > 1 || counter[2] > 1)
		error_exit("too many ambient/camera/light in the scene");
}

/*parse args to correct format*/
void	parse_args()
{
	int		i;
	int	counter[3];
	char	**tmp;
	
	i = -1;
	ft_bzero(counter, 3 * sizeof(int));
	while (s()->args[++i])
	{
		tmp = ft_split(s()->args[i], ' ');
		if (!tmp)
			error_exit("mistake happend when split file content");
		if (!parse_line(counter, tmp))
		{
			free_matrix(tmp);
			error_exit("mistake happend for file format");
		}
		free_matrix(tmp);
	}
	check_counter(counter);
	
}
