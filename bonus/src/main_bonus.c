

#include "miniRT_bonus.h"

static long	get_time_diff(struct timeval *start, struct timeval *end)
{
	return (((end->tv_sec - start->tv_sec) * 1000000L)
		+ (end->tv_usec - start->tv_usec));
}

void	control_frame_rate(void)
{
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = get_time_diff(&s()->last_frame_time, &current_time);
	if (elapsed_time >= FRAME_TIME)
	{
		s()->last_frame_time = current_time;
		fake_render();
	}
	else
		usleep(FRAME_TIME - elapsed_time);
}

int	main(int argc, char **argv)
{
	printf("bonus\n");
	if (argc != 2)
		error_exit("need and only need one argument");
	init_scene(argv[1]);
	render();
	mlx_do_key_autorepeatoff(s()->win.mlx);
	mlx_hook(s()->win.disp, KeyPress, KeyPressMask, press_key, &s()->keys);
	mlx_hook(s()->win.disp, KeyRelease, KeyReleaseMask,
		release_key, &s()->keys);
	// need to adjust later maybe
	mlx_hook(s()->win.disp, DestroyNotify, StructureNotifyMask, ft_quit, NULL);
	mlx_loop_hook(s()->win.mlx, update, &s()->keys);
	mlx_loop(s()->win.mlx);
	delete_scene();
	return (SUCCESS);
}
