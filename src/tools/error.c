/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:24:37 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 10:16:17 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	delete_fclass(t_fclass *fclass)
{
	if (!fclass->array)
	{
		write(1, "here\n", 5);
		return ;
	}
	free_matrix((char **)fclass->array);
	free(fclass);
}

void	delete_scene()
{
	delete_fclass(s()->light);
	delete_fclass(s()->shapes);
	free_matrix(s()->map);
}

void	show_message(char *message)
{
	delete_scene();
	printf("Error: %s\n", message);
	exit(FAIL_STD);
}
