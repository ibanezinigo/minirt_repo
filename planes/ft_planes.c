/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_planes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:49:54 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:23:14 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_planes.h"

t_shape	ft_plane(void)
{
	t_shape	plane;

	plane.transform = ft_identity_matrix();
	plane.material = ft_material();
	plane.shape_type = 2;
	return (plane);
}

t_tuple	ft_normal_at_plane(void)
{
	return (ft_create_vector(0, 1, 0));
}

t_intersections	ft_plane_intersect(t_shape plane, t_ray ray)
{
	t_intersections	inter;

	if (fabs(ray.direction.y) < 0.00001)
	{
		inter.count = 0;
		inter.xs = NULL;
		return (inter);
	}
	inter.count = 1;
	inter.xs = malloc(sizeof(t_intersection) * 1);
	inter.xs[0].object = plane;
	inter.xs[0].t = (ray.origin.y * -1) / ray.direction.y;
	return (inter);
}
