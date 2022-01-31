/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cones.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:10:07 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 17:33:36 by iibanez-         ###   ########.fr       */
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


t_intersections	ft_intersect_caps_2(t_shape cone, t_ray ray, t_intersections inter)
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

t_intersections	ft_cones_intersect(t_shape cone, t_ray ray)
{
	t_intersections	inter;
	float			a;
	float			b;
	float			c;
	float			disc;
	float			t0;
	float			t1;
	float			y0;
	float			y1;
	
	inter.xs = malloc(sizeof(t_intersection) * 4);
	a = powf(ray.direction.x, 2) - powf(ray.direction.y, 2) + powf(ray.direction.z, 2);
	b = 2 * ray.origin.x * ray.direction.x -
		2 * ray.origin.y * ray.direction.y +
		2 * ray.origin.z * ray.direction.z;
	if (a < 0.00001 && a > -0.00001 && b < 0.00001 && b > -0.00001 )
		return (ft_intersect_caps_2(cone, ray, inter));
	c = powf(ray.origin.x, 2) - powf(ray.origin.y, 2) + powf(ray.origin.z, 2);
	if (a < 0.00001 && a > -0.00001)
	{
		inter.xs[inter.count] = ft_intersection(c * -1 / (2 * b), cone);
		inter.count = 1;
		return (ft_intersect_caps_2(cone, ray, inter));
	}
	disc = pow(b, 2) - 4 * a * c;
	if (disc <= -0.00001)
	{
		free(inter.xs);
		return (ft_void_inter_2());
	}
	else
	{
		if (disc < 0)
			disc = 0;
		t0 = (b * -1 - sqrtf(disc)) / (2 * a);
		t1 = (b * -1 + sqrtf(disc)) / (2 * a);
		if (t0 > t1)
		{
			t0 = t1;
			t1 = (b * -1 + sqrtf(disc)) / (2 * a);
		}
		inter.count = 0;
		y0 = ray.origin.y + t0 * ray.direction.y;
		if (cone.minimum < y0  && y0 < cone.maximum)
		{
			inter.xs[inter.count] = ft_intersection(t0, cone);
			inter.count = inter.count + 1;
		}
		y1 = ray.origin.y + t1 * ray.direction.y;
		if (cone.minimum < y1 && y1 < cone.maximum)
		{
			inter.xs[inter.count] = ft_intersection(t1, cone);
			inter.count = inter.count + 1;
		}
		return (ft_intersect_caps_2(cone, ray, inter));
	}
}

t_tuple	ft_normal_at_cone(t_shape cone, t_tuple point)
{
	float	dist;
	float	y;

	dist = powf(point.x, 2) + powf(point.z, 2);
	if (dist < 1 && point.y >= (cone.maximum - 0.00001))
		return (ft_create_vector(0, 1, 0));
	else if (dist < 1 && point.y <= (cone.minimum + 0.00001))
		return (ft_create_vector(0, -1, 0));
	else
	{
		y = sqrtf(powf(point.x, 2) + powf(point.z, 2));
		if (point.y > 0)
			y = y * -1;
		return (ft_create_vector(point.x, y, point.z));
	}
}
