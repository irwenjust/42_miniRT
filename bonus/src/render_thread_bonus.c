#include "miniRT_bonus.h"
#include <pthread.h>

void	*sample_region(void *arg)
{
	t_thread_data	*data;

	t_hit		closest;
	t_vector	cur;
	t_vector	converted_cur;
	t_ray		ray;

	

	data = (t_thread_data *)arg;
	cur.y = data->start_y;
	while (cur.y < data->end_y)
	{
		cur.x = data->start_x;
		while (cur.x < data->end_x)
		{
			closest = init_hit();
			converted_cur = convert_viewport(cur.x, cur.y);
			ray = make_ray(converted_cur);
			if (check_intersection(s()->shapes, &ray, &closest))
				check_illumination(&closest);
			put_pixel(closest.color, cur.x, cur.y);
			cur.x++;
		}
		
		cur.y++;
	}
	return (NULL);
}

void	render_thread(void)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	data[NUM_THREADS];
	int				i;

	i = 0;
	while (i < NUM_THREADS)
	{
		data[i].start_x = 0;
		data[i].end_x = WIDTH;
		data[i].start_y = i * (HEIGHT / NUM_THREADS);
		data[i].end_y = (i + 1) * (HEIGHT / NUM_THREADS);
		pthread_create(&threads[i], NULL, sample_region, &data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.img, 0, 0);
	display_menu();
}