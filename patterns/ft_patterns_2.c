/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patterns_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:51:31 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 15:53:41 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_patterns.h"

t_color	ft_pattern_at(t_tuple point)
{
	t_color	c;

	c.red = point.x;
	c.green = point.y;
	c.blue = point.z;
	return (c);
}

t_color	ft_pattern_at_gradient(t_pattern p, t_tuple point)
{
	t_color	c;
	t_color	distance;
	float	fraction;

	distance = ft_color_subtract(p.b, p.a);
	fraction = point.x - floorf(fabs(point.x));
	c = ft_color_add(p.a, ft_color_multiply_byscalar(distance, fraction));
	return (c);
}

t_color	ft_pattern_at_ring(t_pattern p, t_tuple point)
{
	float	ca;

	ca = fmod(sqrt(pow(point.x, 2) + pow(point.z, 2)), 2);
	if (ca < 1)
		return (p.a);
	else
		return (p.b);
}

t_color	ft_pattern_at_checker(t_pattern p, t_tuple point)
{
	float	ca;
	float	total;

	total = fabs(floorf(point.x)) + fabs(floorf(point.y))
		+ fabs(floorf(point.z));
	ca = fmod(total, 2);
	if (ca < 1)
		return (p.a);
	else
		return (p.b);
}

t_color	ft_pattern_at_shape(t_pattern pattern, t_shape shape, t_tuple point)
{
	t_tuple	object_point;
	t_tuple	pattern_point;

	object_point = ft_multiply_matrix_tuple(
			ft_inverse(shape.transform), point);
	pattern_point = ft_multiply_matrix_tuple(
			ft_inverse(pattern.transform), object_point);
	if (pattern.pattern_type == 1)
		return (ft_pattern_at(pattern_point));
	if (pattern.pattern_type == 2)
		return (ft_pattern_at_gradient(pattern, pattern_point));
	if (pattern.pattern_type == 3)
		return (ft_pattern_at_ring(pattern, pattern_point));
	if (pattern.pattern_type == 4)
		return (ft_pattern_at_checker(pattern, pattern_point));
	else
	{
		printf("Error ft_pattern_at_shape\n");
		return (ft_stripe_at(pattern, pattern_point));
	}
}
