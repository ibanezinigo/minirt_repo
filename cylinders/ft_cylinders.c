/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:39:36 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 17:41:21 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cylinders.h"

t_shape	ft_cylinder(void)
{
	t_shape	cylinder;

	cylinder.transform = ft_matrix_translation(0, 0, 0);
	cylinder.material = ft_material();
	cylinder.shape_type = 3;
	cylinder.minimum = INFINITY * -1;
	cylinder.maximum = INFINITY;
	cylinder.closed = 0;
	return (cylinder);
}

t_intersections	ft_void_inter(void)
{
	t_intersections	inter;

	inter.count = 0;
	inter.xs = NULL;
	return (inter);
}

int	ft_check_cap(t_ray ray, float t)
{
	float	x;
	float	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((powf(x, 2) + powf(z, 2)) <= 1.00001)
		return (1);
	else
		return (0);
}

t_intersections	ft_intersect_caps(t_shape cyl, t_ray ray, t_intersections inter)
{
	float			t;

	if (cyl.closed == 1)
	{
		t = (cyl.minimum - ray.origin.y) / ray.direction.y;
		if (ft_check_cap(ray, t))
		{
			inter.xs[inter.count] = ft_intersection(t, cyl);
			inter.count = inter.count + 1;
		}
		t = (cyl.maximum - ray.origin.y) / ray.direction.y;
		if (ft_check_cap(ray, t))
		{
			inter.xs[inter.count] = ft_intersection(t, cyl);
			inter.count = inter.count + 1;
		}
	}
	if (inter.count == 0)
	{
		free(inter.xs);
		inter.xs = NULL;
	}
	return (inter);
}
