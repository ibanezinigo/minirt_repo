/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:55:18 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/28 15:54:51 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_intersections.h"

t_intersections	ft_sphere_intersect(t_shape s, t_ray r)
{
	t_intersections	inter;
	t_tuple			sph_to_ray;
	float			a;
	float			b;
	float			c;
	float			discrimininant;

	sph_to_ray = ft_subtract_tuples(r.origin, ft_create_point(0, 0, 0));
	a = ft_tuple_dot(r.direction, r.direction);
	b = 2 * ft_tuple_dot(r.direction, sph_to_ray);
	c = ft_tuple_dot(sph_to_ray, sph_to_ray) - 1;
	discrimininant = (pow(b, 2) - (4 * a * c));
	if (discrimininant < 0)
	{
		inter.count = 0;
		inter.xs = NULL;
		return (inter);
	}
	else
	{
		inter.count = 2;
		inter.xs = malloc(sizeof(t_intersection) * inter.count);
		inter.xs[0].t = (-b - sqrt(discrimininant)) / (2 * a);
		inter.xs[0].object = s;
		inter.xs[1].t = (-b + sqrt(discrimininant)) / (2 * a);
		inter.xs[1].object = s;
		return (inter);
	}
}

t_intersection	ft_intersection(float t, t_shape s)
{
	t_intersection	i;

	i.t = t;
	i.object = s;
	return (i);
}

t_intersections	ft_intersections(t_intersections base, t_intersection inter)
{
	t_intersections	intersections;
	int				i;

	intersections.count = base.count + 1;
	intersections.xs = malloc(sizeof(t_intersection) * intersections.count);
	i = 0;
	while (i < intersections.count - 1)
	{
		intersections.xs[i] = base.xs[i];
		i++;
	}
	intersections.xs[i] = inter;
	return (intersections);
}

t_intersection	ft_hit(t_intersections inter)
{
	int				minpos;
	int				minvalue;
	int				i;
	t_intersection	nul;

	if (inter.count == 0)
	{
		nul.t = -1;
		return (nul);
	}
	minpos = -1;
	minvalue = -1;
	i = 0;
	while (i < inter.count)
	{
		if ((inter.xs[i].t < minvalue || minvalue == -1) && inter.xs[i].t >= 0)
		{
			minpos = i;
			minvalue = inter.xs[i].t;
		}
		i++;
	}
	if (minpos == -1)
	{
		nul.t = -1;
		return (nul);
	}
	return (inter.xs[minpos]);
}

t_intersections	ft_add_intersections(t_intersections dest, t_intersections new)
{
	t_intersections	result;
	int				i;
	int				saved;

	result.count = dest.count + new.count;
	result.xs = malloc(sizeof(t_intersection) * result.count);
	saved = 0;
	i = 0;
	while (i < dest.count)
	{
		result.xs[saved] = dest.xs[i];
		saved++;
		i++;
	}
	i = 0;
	while (i < new.count)
	{
		result.xs[saved] = new.xs[i];
		saved++;
		i++;
	}
	if (dest.count > 0)
		free(dest.xs);
	if (new.count > 0)
		free(new.xs);
	return (result);
}

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
