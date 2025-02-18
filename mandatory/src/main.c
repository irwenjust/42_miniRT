/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:54:26 by likong            #+#    #+#             */
/*   Updated: 2025/02/18 10:06:07 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	printf("mandatory\n");
	if (argc != 2)
		error_exit("need and only need one argument");
	init_scene(argv[1]);
	render();
	mlx_do_key_autorepeatoff(s()->win.mlx);
	mlx_hook(s()->win.disp, KeyPress, KeyPressMask, press_key, &s()->keys);
	mlx_hook(s()->win.disp, KeyRelease, KeyReleaseMask,
		release_key, &s()->keys);
	mlx_hook(s()->win.disp, DestroyNotify, StructureNotifyMask, ft_quit, NULL);
	mlx_loop_hook(s()->win.mlx, update, &s()->keys);
	mlx_loop(s()->win.mlx);
	delete_scene();
	return (SUCCESS);
}
