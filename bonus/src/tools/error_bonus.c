

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

void	free_test_matrix(void **matrix)
{
	size_t	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	delete_scene(void)
{
	delete_fclass(s()->light);
	delete_fclass(s()->shapes);
	delete_fclass(s()->ori_light);
	delete_fclass(s()->ori_shapes);
	free_test_matrix((void **)s()->args);
	if (s()->win.img)
		mlx_destroy_image(s()->win.mlx, s()->win.img);
	if (s()->win.menu)
		mlx_destroy_image(s()->win.mlx, s()->win.menu);
	if (s()->win.disp)
		mlx_destroy_window(s()->win.mlx, s()->win.disp);
	if (s()->win.cboard)
		mlx_destroy_image(s()->win.mlx, s()->win.cboard);
	// free_test_matrix((void **)s()->cboard);
	ft_free(s()->cboard);
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
