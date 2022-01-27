/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patterns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:26:55 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 16:17:37 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_patterns.h"
# include "ft_spheres.h"

t_pattern ft_stripe_pattern(t_color a, t_color b)
{
    t_pattern p;

    p.a = a;
    p.b = b;
    p.transform = ft_matrix(4, 4);
    p.transform.data[0][0] = 1;
    p.transform.data[1][1] = 1;
    p.transform.data[2][2] = 1;
    p.transform.data[3][3] = 1;
    return (p);
}

t_color ft_stripe_at(t_pattern p, t_tuple point)
{
    float pos;

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
t_color ft_stripe_at_object(t_pattern pattern, t_sphere s, t_tuple world_point)
{
    t_tuple object_point;
    t_tuple pattern_point;

    object_point = ft_multiply_matrix_tuple(ft_inverse(s.transform), world_point);
    pattern_point = ft_multiply_matrix_tuple(ft_inverse(pattern.transform), object_point);
    return (ft_stripe_at(pattern, pattern_point));
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