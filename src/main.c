/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:54:26 by likong            #+#    #+#             */
/*   Updated: 2024/11/22 11:49:07 by likong           ###   ########.fr       */
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
// 	// 	int new_width = xevent->xconfigure.width;dc
// 	// 	int new_height = xevent->xconfigure.height;

// 	// 	if (new_width != s()->view_w || new_height != s()->view_h)
// 	// 	{
// 	// 		s()->view_h = new_height;
// 	// 		s()->view_w = new_width;
// 	// 	}
// 	// }
// 	return (0);
// }

static long get_time_diff(struct timeval *start, struct timeval *end)
{
    return ((end->tv_sec - start->tv_sec) * 1000000L) + (end->tv_usec - start->tv_usec);
}

void	control_frame_rate()
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

    long elapsed_time = get_time_diff(&s()->last_frame_time, &current_time);

    if (elapsed_time >= FRAME_TIME)
	{
        s()->last_frame_time = current_time;
        fake_render();
    } 
	else
        usleep(FRAME_TIME - elapsed_time);
}

// static int	control_center()
// {
// 	if (s()->menu.mode == VIEW)
// 	{
// 		render();
// 		// printf("render\n");
// 	}
// 	else if (s()->menu.mode == CAMERA)
// 		control_frame_rate();
// 	return (0);
// }

int	ft_quit()  //may change to void
{
	delete_scene();
	exit(SUCCESS);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		error_exit("need and only need one argument");
	init_scene(argv[1]);
	render();
	
	//new key hook
	ft_bzero(&(s()->keys), sizeof(t_key));
	s()->keys.cur_keycode = -1;
	mlx_hook(s()->win.disp, KeyPress, KeyPressMask, press_key, &s()->keys);
	mlx_hook(s()->win.disp, KeyRelease, KeyReleaseMask, release_key, &s()->keys);
	mlx_loop_hook(s()->win.mlx, update, &s()->keys);
	//end new key hook

	// mlx_key_hook(s()->win.disp, key_press, NULL);
	// mlx_hook(s()->win.disp, KeyPress, KeyPressMask, key_keep_press, NULL);
	// mlx_hook(s()->win.disp, KeyRelease, KeyReleaseMask, key_release, NULL);
	// mlx_loop_hook(s()->win.mlx, );
	// render();
	// print_shape((t_shape *)s()->shapes->array[2]);
	// mlx_hook(s()->win.disp, ConfigureNotify, StructureNotifyMask, resize_win, NULL);
	// mlx_loop_hook(s()->win.mlx, (void *)resize_win, NULL);
	mlx_hook(s()->win.disp, DestroyNotify, StructureNotifyMask, ft_quit, NULL); // need to adjust later maybe
	// mlx_loop_hook(s()->win.mlx, control_center, NULL);
	mlx_loop(s()->win.mlx);
	// print_shape((t_shape *)s()->shapes->array[1]);
	delete_scene();
	return (SUCCESS);
}