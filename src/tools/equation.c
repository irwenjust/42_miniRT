/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:35:01 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/27 14:10:45 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Check whether there is a result of √(b^2 -4ac), 
 * (b^2 -4ac) must be greater than 0
 */
static double has_valid_sqrt(t_equation *equation)
{
	double res;

	res = pow(equation->b, 2) - (4 * equation->a * equation->c);
	if (res < 0)
		return (-1);
	return (res);
}

/**
 * @brief solve the equation at^2 + bt + c = 0, to get the t value
 * there are 4 cases:
 * 		1-if a==0, b!=0 ---> bt + c = 0 ---> t = -c/b
 * 		2-if a!=0, b==0 ---> at^2 + c = 0 ---> t = √(-c/a)
 * 		3-if a!=0, b!=0, c==0 ---> at^2 + bt = 0 ---> t = -b/a
 * 		4-if a!=0, b!=0, c!=0
 * 			t^2 + (b/a)t = -(c/a)
 * 			t^2 + (b/a)t + (b/2a)^2 = -(c/a) + (b/2a)^2
 * 			(t + b/2a)^2 = (b^2 - 4ac) / 4a^2
 * 			t + b/2a = ±√(b^2 -4ac) / 2a
 * 			t = (-b ± √(b^2 -4ac)) / 2a
 * 		case2&3 can be handled in case4
 */
bool solve(t_equation *equation)
{
	double res;

	res = 0;
	if (equation->a == 0.0 && equation->b != 0.0)
		equation->t1 = -equation->c / equation->b;
	else
	{
		res = has_valid_sqrt(equation);
		if (res < 0)
			return (false);
		equation->t1 = (-equation->b - sqrt(res)) / (2 * equation->a);
		equation->t2 = (-equation->b + sqrt(res)) / (2 * equation->a);
	}
	return (true);
}
