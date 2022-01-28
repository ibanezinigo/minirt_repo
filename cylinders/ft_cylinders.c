/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:39:36 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/28 20:15:16 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cylinders.h"

t_shape	ft_cylinder()
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
		//printf("%f\n", t);
		if (ft_check_cap(ray, t))
		{
			//printf("cap1 count: %i\n", inter.count);
			inter.xs[inter.count] = ft_intersection(t, cyl);
			inter.count = inter.count + 1;
		}
		t = (cyl.maximum - ray.origin.y) / ray.direction.y;
		//printf("%f\n", t);
		if (ft_check_cap(ray, t))
		{
			//printf("cap2 count: %i\n", inter.count);
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

t_intersections	ft_cylinders_intersect(t_shape cyl, t_ray ray)
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
	
	inter.xs = malloc(sizeof(t_intersection) * 2);
	a = powf(ray.direction.x, 2) + powf(ray.direction.z, 2);
	if (a < 0.00001 && a > 0.00001)
		return (ft_intersect_caps(cyl, ray, inter));
	b = 2 * ray.origin.x * ray.direction.x +
		2 * ray.origin.z * ray.direction.z;
	c = powf(ray.origin.x, 2) + powf(ray.origin.z, 2) - 1;
	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
	{
		free(inter.xs);
		return (ft_void_inter());
	}
	else
	{
		t0 = (b * -1 - sqrtf(disc)) / (2 * a);
		t1 = (b * -1 + sqrtf(disc)) / (2 * a);
		if (t0 > t1)
		{
			t0 = t1;
			t1 = (b * -1 + sqrtf(disc)) / (2 * a);
		}
		inter.count = 0;
		y0 = ray.origin.y + t0 * ray.direction.y;
		if (cyl.minimum < y0  && y0 < cyl.maximum)
		{
			inter.xs[inter.count] = ft_intersection(t0, cyl);
			inter.count = inter.count + 1;
		}
		y1 = ray.origin.y + t1 * ray.direction.y;
		if (cyl.minimum < y1 && y1 < cyl.maximum)
		{
			inter.xs[inter.count] = ft_intersection(t1, cyl);
			inter.count = inter.count + 1;
		}
		return (ft_intersect_caps(cyl, ray, inter));
	}
}

t_tuple	ft_normal_at_cylinder(t_shape cylinder, t_tuple point)
{
	float	dist;

	dist = powf(point.x, 2) + powf(point.z, 2);
	if (dist < 1 && point.y >= (cylinder.maximum - 0.00001))
		return (ft_create_vector(0, 1, 0));
	else if (dist < 1 && point.y <= (cylinder.minimum + 0.00001))
		return (ft_create_vector(0, -1, 0));
	else
		return (ft_create_vector(point.x, 0, point.z));
}
