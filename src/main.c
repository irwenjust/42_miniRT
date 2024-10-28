/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:54:26 by likong            #+#    #+#             */
/*   Updated: 2024/10/28 10:19:08 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		show_message("need and only need one argument");
	init_scene(argv[1]);
	// print_shape((t_shape *)s()->shapes->array[3]);
	delete_scene();
	
	// init_point();
	// init_vector();

	// printf("point x: %lf, point y: %lf, point z: %lf, point type: %d\n", p()->x, p()->y, p()->z, p()->type);
	// printf("vector x: %lf, vector y: %lf, vector z: %lf, vector type: %d\n", v()->x, v()->y, v()->z, v()->type);
	
	return (SUCCESS);
}