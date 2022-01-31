/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patterns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:26:55 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 16:07:50 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_patterns.h"
#include "ft_spheres.h"

t_pattern	ft_stripe_pattern(t_color a, t_color b)
{
	t_pattern	p;

	p.a = a;
	p.b = b;
	p.transform = ft_matrix(4, 4);
	p.transform.data[0][0] = 1;
	p.transform.data[1][1] = 1;
	p.transform.data[2][2] = 1;
	p.transform.data[3][3] = 1;
	p.pattern_type = 1;
	return (p);
}

t_pattern	ft_gradient_pattern(t_color a, t_color b)
{
	t_pattern	p;
	p.a = a;
	p.b = b;
	p.transform = ft_matrix(4, 4);
	p.transform.data[0][0] = 1;
	p.transform.data[1][1] = 1;
	p.transform.data[2][2] = 1;
	p.transform.data[3][3] = 1;
	p.pattern_type = 2;
	return (p);
}

t_pattern	ft_ring_pattern(t_color a, t_color b)
{
	t_pattern	p;

	p.a = a;
	p.b = b;
	p.transform = ft_matrix(4, 4);
	p.transform.data[0][0] = 1;
	p.transform.data[1][1] = 1;
	p.transform.data[2][2] = 1;
	p.transform.data[3][3] = 1;
	p.pattern_type = 3;
	return (p);
}

t_pattern	ft_checker_pattern(t_color a, t_color b)
{
	t_pattern	p;

	p.a = a;
	p.b = b;
	p.transform = ft_matrix(4, 4);
	p.transform.data[0][0] = 1;
	p.transform.data[1][1] = 1;
	p.transform.data[2][2] = 1;
	p.transform.data[3][3] = 1;
	p.pattern_type = 4;
	return (p);
}

t_color	ft_stripe_at(t_pattern p, t_tuple point)
{
	float	pos;

	if (point.x < 0)
	{
		pos = point.x * -1;
		if (pos <= 1)
			return (p.b);
		else
			return (p.a);
	}
	else
	{
		if (point.x < 1)
			return (p.a);
		else
			return (p.b);
	}
}

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
	t_color	c;
	float	ca;
	
	ca = fmod(sqrt(pow(point.x, 2) + pow(point.z, 2)), 2);
	if (ca < 1)
		return (p.a);
	else
		return (p.b);
}

t_color	ft_pattern_at_checker(t_pattern p, t_tuple point)
{
	t_color	c;
	float	ca;
	float	total;

	total = fabs(floorf(point.x)) + fabs(floorf(point.y)) + fabs(floorf(point.z));
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

void	ft_set_pattern_transform(t_pattern s, t_matrix translation)
{
	int	x;
	int	y;

	y = 0;
	while (y < s.transform.rows && y < translation.rows)
	{
		x = 0;
		while (x < s.transform.cols && y < translation.cols)
		{
			s.transform.data[y][x] = translation.data[y][x];
			x++;
		}
		y++;
	}
}
