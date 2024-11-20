/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:54:26 by likong            #+#    #+#             */
/*   Updated: 2024/11/20 11:30:11 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static int resize_win()
// {
// 	XWindowAttributes attrs;
// 	XGetWindowAttributes(s()->win.display, s()->win.window, &attrs);
// 	// XEvent *xevent = (XEvent *)event;

// 	if (attrs.width != s()->win.width || attrs.height != s()->win.height)
// 	{
// 		s()->win.width = attrs.width;
// 		s()->win.height = attrs.height;
		
// 		// mlx_clear_window(s()->win.mlx, s()->win.disp);
// 	}
// 	// if (xevent->type == ConfigureNotify)
// 	// {
// 	// 	int new_width = xevent->xconfigure.width;
// 	// 	int new_height = xevent->xconfigure.height;

// 	// 	if (new_width != s()->view_w || new_height != s()->view_h)
// 	// 	{
// 	// 		s()->view_h = new_height;
// 	// 		s()->view_w = new_width;
// 	// 	}
// 	// }
// 	return (0);
// }

int	main(int argc, char **argv)
{
	if (argc != 2)
		error_exit("need and only need one argument");
	init_scene(argv[1]);

	
	render();
	print_shape((t_shape *)s()->shapes->array[2]);
	// mlx_hook(s()->win.disp, ConfigureNotify, StructureNotifyMask, resize_win, NULL);
	// mlx_loop_hook(s()->win.mlx, (void *)resize_win, NULL);
	mlx_hook(s()->win.disp, KeyPress, KeyPressMask, ft_keypress, NULL);
	mlx_hook(s()->win.disp, DestroyNotify, StructureNotifyMask, ft_quit, NULL); // need to adjust later maybe
	mlx_loop(s()->win.mlx);
	print_shape((t_shape *)s()->shapes->array[1]);
	delete_scene();
	return (SUCCESS);
}