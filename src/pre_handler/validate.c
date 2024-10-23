/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:10:38 by likong            #+#    #+#             */
/*   Updated: 2024/10/22 09:19:29 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	validate_filename(char *f_name)
{
	//if string length < 3?
	if (ft_strncmp(f_name + ft_strlen(f_name) - 3, ".rt", 3))
		return (false);
	return (true);
}
