/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patterns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:26:55 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 15:54:07 by iibanez-         ###   ########.fr       */
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
