/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:44:24 by likong            #+#    #+#             */
/*   Updated: 2024/10/28 15:23:58 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	put_pixel(t_color c, int x, int y)
{
	char *dst;

	dst = s()->win.addr + (y * WIDTH + x) * (s()->win.bpp / 8);
	*(unsigned int *)dst = (c.alpha << 24 | c.red << 16 | c.green << 8 | c.blue);
}
