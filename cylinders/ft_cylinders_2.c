/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinders_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:07:32 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 17:31:34 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cylinders.h"

t_intersections	ft_cyl_inter_aux(t_shape cyl, t_ray ray, float t0, float t1)
{
	t_intersections	inter;
	float			ttemp;

	inter.xs = malloc(sizeof(t_intersection) * 4);
	if (t0 > t1)
	{
		ttemp = t0;
		t0 = t1;
		t1 = ttemp;
	}
	inter.count = 0;
	if (ft_is_between(cyl.minimum, cyl.maximum,
			ray.origin.y + t0 * ray.direction.y))
	{
		inter.xs[inter.count] = ft_intersection(t0, cyl);
		inter.count = inter.count + 1;
	}
	if (ft_is_between(cyl.minimum, cyl.maximum,
			ray.origin.y + t1 * ray.direction.y))
	{
		inter.xs[inter.count] = ft_intersection(t1, cyl);
		inter.count = inter.count + 1;
	}
	return (ft_intersect_caps(cyl, ray, inter));
}

t_intersections	ft_cylinders_intersect(t_shape cyl, t_ray ray)
{
	t_intersections	inter;
	float			a;
	float			b;
	float			c;
	float			disc;

	inter.xs = malloc(sizeof(t_intersection) * 4);
	a = powf(ray.direction.x, 2) + powf(ray.direction.z, 2);
	if (a < 0.00001 && a > 0.00001)
		return (ft_intersect_caps(cyl, ray, inter));
	b = 2 * ray.origin.x * ray.direction.x
		+ 2 * ray.origin.z * ray.direction.z;
	c = powf(ray.origin.x, 2) + powf(ray.origin.z, 2) - 1;
	disc = pow(b, 2) - 4 * a * c;
	free(inter.xs);
	if (disc < 0)
		return (ft_void_inter());
	else
		inter = ft_cyl_inter_aux(cyl, ray, (b * -1 - sqrtf(disc)) / (2 * a),
				(b * -1 + sqrtf(disc)) / (2 * a));
	return (inter);
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
