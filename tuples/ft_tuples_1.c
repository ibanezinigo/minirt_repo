/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tuples_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:20:57 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:21:45 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tuples.h"

t_tuple	ft_divide_tuple(t_tuple t1, float s)
{
	return (ft_multiply_tuple(t1, 1 / s));
}

t_tuple	ft_negate_tuple(t_tuple t1)
{
	return (ft_multiply_tuple(t1, -1));
}

float	ft_tuple_magnitude(t_tuple t)
{
	float	result;

	result = 0;
	result += powf(t.x, 2);
	result += powf(t.y, 2);
	result += powf(t.z, 2);
	result += powf(t.w, 2);
	result = sqrt(result);
	return (result);
}

t_tuple	ft_tuple_normalize(t_tuple t)
{
	float	magnitude;

	magnitude = ft_tuple_magnitude(t);
	return (ft_divide_tuple(t, magnitude));
}

float	ft_tuple_dot(t_tuple t1, t_tuple t2)
{
	float	r;

	r = 0;
	r += t1.x * t2.x;
	r += t1.y * t2.y;
	r += t1.z * t2.z;
	r += t1.w * t2.w;
	return (r);
}
