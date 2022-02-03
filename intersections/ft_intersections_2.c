/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersections_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 18:28:20 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 18:28:35 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_intersections.h"

t_comps	ft_prepare_computations(t_intersection inter, t_ray ray)
{
	t_comps	comp;

	comp.t = inter.t;
	comp.object = inter.object;
	comp.point = ft_ray_position(ray, comp.t);
	comp.eyev = ft_multiply_tuple(ray.direction, -1);
	comp.normalv = ft_normal_at(comp.object, comp.point);
	if (ft_tuple_dot(comp.normalv, comp.eyev) < 0)
	{
		comp.inside = 1;
		comp.normalv = ft_multiply_tuple(comp.normalv, -1);
	}
	else
		comp.inside = 0;
	comp.over_point = ft_add_tuples(comp.point,
			ft_multiply_tuple(comp.normalv, 0.0001));
	return (comp);
}
