/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cones.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:10:07 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 17:38:55 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cones.h"

t_shape	ft_cone(void)
{
	t_shape	cone;

	cone.transform = ft_identity_matrix();
	cone.material = ft_material();
	cone.shape_type = 4;
	cone.minimum = INFINITY * -1;
	cone.maximum = INFINITY;
	cone.closed = 0;
	return (cone);
}

t_intersections	ft_void_inter_2(void)
{
	t_intersections	inter;

	inter.count = 0;
	inter.xs = NULL;
	return (inter);
}

int	ft_check_cap_2(t_ray ray, float t)
{
	float	x;
	float	z;
	float	y;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	y = ray.origin.y + t * ray.direction.y;
	if ((powf(x, 2) + powf(z, 2)) <= fabs(y))
		return (1);
	else
		return (0);
}

t_intersections	ft_intersect_caps_2(t_shape cone,
		t_ray ray, t_intersections inter)
{
	float			t;

	if (cone.closed == 1)
	{
		t = (cone.minimum - ray.origin.y) / ray.direction.y;
		if (ft_check_cap_2(ray, t))
		{
			inter.xs[inter.count] = ft_intersection(t, cone);
			inter.count = inter.count + 1;
		}
		t = (cone.maximum - ray.origin.y) / ray.direction.y;
		if (ft_check_cap_2(ray, t))
		{
			inter.xs[inter.count] = ft_intersection(t, cone);
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

t_intersections	ft_cones_aux(t_shape cone, t_ray ray, float t0, float t1)
{
	float			ttemp;
	t_intersections	inter;	

	inter.xs = malloc(sizeof(t_intersection) * 4);
	if (t0 > t1)
	{
		ttemp = t0;
		t0 = t1;
		t1 = ttemp;
	}
	inter.count = 0;
	if (ft_is_between(cone.minimum, cone.maximum,
			ray.origin.y + t0 * ray.direction.y))
	{
		inter.xs[inter.count] = ft_intersection(t0, cone);
		inter.count = inter.count + 1;
	}
	if (ft_is_between(cone.minimum, cone.maximum,
			ray.origin.y + t1 * ray.direction.y))
	{
		inter.xs[inter.count] = ft_intersection(t1, cone);
		inter.count = inter.count + 1;
	}
	return (inter);
}
