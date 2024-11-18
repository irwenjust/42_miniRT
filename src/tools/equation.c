/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:35:01 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/18 17:52:25 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double calculate(t_equation *equation)
{
	double res;

	res = pow(equation->b, 2) - (4 * equation->a * equation->c);
	if (res < 0)
		return (-1);
	return (res);
}

double solve(t_equation *equation)
{
	double res;

	if (equation->a == 0.0 && equation->b != 0.0)
	{
		equation->t1 = -equation->c / equation->b;
		return (0);
	}
	else
	{
		res = calculate(equation);
		if (res < 0)
			return (-1);
		equation->t1 = (-equation->b - sqrt(res)) / (2 * equation->a);
		equation->t2 = (-equation->b + sqrt(res)) / (2 * equation->a);
		return (res);
	}
}
