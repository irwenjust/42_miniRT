/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:54:05 by likong            #+#    #+#             */
/*   Updated: 2024/10/24 17:54:54 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_counter(int counter[3])
{
	if (counter[0] == 0)
		show_message("No ambient in the scene");
	else if (counter[1] == 0)
		show_message("No camera in the scene");
	else if (counter[2] == 0)
		show_message("No light in the scene");
	else if (counter[0] > 1 || counter[1] > 1 || counter[2] > 1)
		show_message("too many ambient/camera/light in the scene");
}
