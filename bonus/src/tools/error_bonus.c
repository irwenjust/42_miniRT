

#include "miniRT_bonus.h"

static void	delete_fclass(t_fclass *fclass)
{
	if (!fclass)
		return ;
	free_matrix((char **)fclass->array);
	free(fclass);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

// void	lst_clear(t_list **lst)
// {
// 	t_list	*res;

// 	if (!lst)
// 		return ;
// 	while (*lst)
// 	{
// 		res = (*lst)->next;
// 		free(*lst);
// 		*lst = res;
// 	}
// }

void	delete_scene(void)
{
	delete_fclass(s()->light);
	delete_fclass(s()->shapes);
	delete_fclass(s()->ori_light);
	delete_fclass(s()->ori_shapes);
	// lst_clear(&s()->unbound);
	free_matrix(s()->args);
	// if (s()->win.img)
	// 	mlx_delete_image(s()->win.mlx, s()->win.img);
	// if (s()->win.mlx)
	// 	mlx_terminate(s()->win.mlx);
	if (s()->win.img)
		mlx_destroy_image(s()->win.mlx, s()->win.img);
	if (s()->win.menu)
		mlx_destroy_image(s()->win.mlx, s()->win.menu);
	if (s()->win.disp)
		mlx_destroy_window(s()->win.mlx, s()->win.disp);
	if (s()->win.mlx)
	{
		mlx_do_key_autorepeaton(s()->win.mlx);
		mlx_destroy_display(s()->win.mlx);
	}
	if (s()->bvh)
		free_bvh(&s()->bvh);
	ft_free(s()->win.mlx);
}

void	error_exit(char *message)
{
	delete_scene();
	printf("Error: %s\n", message);
	exit(FAILURE);
}
