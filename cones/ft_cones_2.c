/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cones_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:39:02 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 17:39:10 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cones.h"

void	ft_calc_vars_cones(t_ray ray, float *a, float *b, float *c)
{
	*a = powf(ray.direction.x, 2) - powf(ray.direction.y, 2)
		+ powf(ray.direction.z, 2);
	*b = 2 * ray.origin.x * ray.direction.x
		- 2 * ray.origin.y * ray.direction.y
		+ 2 * ray.origin.z * ray.direction.z;
	*c = powf(ray.origin.x, 2) - powf(ray.origin.y, 2)
		+ powf(ray.origin.z, 2);
}

t_intersections	ft_cones_intersect(t_shape cone, t_ray ray)
{
	t_intersections	inter;
	float			var[3];
	float			disc;

	ft_calc_vars_cones(ray, &var[0], &var[1], &var[2]);
	if (var[0] < 0.00001 && var[0] > -0.00001)
	{
		inter.xs = malloc(sizeof(t_intersection) * 4);
		if (var[1] < 0.00001 && var[1] > -0.00001)
			return (ft_intersect_caps_2(cone, ray, inter));
		inter.xs[inter.count] = ft_intersection(var[2] * -1 / (2 * var[1]),
				cone);
		inter.count = 1;
		return (ft_intersect_caps_2(cone, ray, inter));
	}
	disc = pow(var[1], 2) - 4 * var[0] * var[2];
	if (disc <= -0.00001)
		return (ft_void_inter_2());
	if (disc < 0)
			disc = 0;
	inter = ft_cones_aux(cone, ray, (var[1] * -1 - sqrtf(disc))
			/ (2 * var[0]), (var[1] * -1 + sqrtf(disc)) / (2 * var[0]));
	return (ft_intersect_caps_2(cone, ray, inter));
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
