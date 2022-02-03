/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:55:18 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 18:28:33 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_intersections.h"

t_intersections	ft_sphere_intersect(t_shape s, t_ray r)
{
	t_intersections	i;
	t_tuple			sph_to_ray;
	float			a;
	float			b;
	float			discrimininant;

	sph_to_ray = ft_subtract_tuples(r.origin, ft_create_point(0, 0, 0));
	a = ft_tuple_dot(r.direction, r.direction);
	b = 2 * ft_tuple_dot(r.direction, sph_to_ray);
	discrimininant = (pow(b, 2)
			- (4 * a * (ft_tuple_dot(sph_to_ray, sph_to_ray) - 1)));
	if (discrimininant < 0)
	{
		i.count = 0;
		i.xs = NULL;
		return (i);
	}
	else
	{
		i.count = 2;
		i.xs = malloc(sizeof(t_intersection) * i.count);
		i.xs[0] = ft_intersection((-b - sqrt(discrimininant)) / (2 * a), s);
		i.xs[1] = ft_intersection((-b + sqrt(discrimininant)) / (2 * a), s);
		return (i);
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

	nul.t = -1;
	if (inter.count == 0)
		return (nul);
	minpos = -1;
	minvalue = -1;
	i = -1;
	while (++i < inter.count)
	{
		if ((inter.xs[i].t < minvalue || minvalue == -1) && inter.xs[i].t >= 0)
		{
			minpos = i;
			minvalue = inter.xs[i].t;
		}
	}
	if (minpos == -1)
		return (nul);
	return (inter.xs[minpos]);
}

t_intersections	ft_add_intersections(t_intersections *dest, t_intersections new)
{
	t_intersections	r;
	int				i;
	int				saved;

	if (new.count > 0)
	{
		r.count = dest->count + new.count;
		r.xs = malloc(sizeof(t_intersection) * r.count);
		saved = 0;
		i = -1;
		while (++i < dest->count)
			r.xs[i] = ft_intersection(dest->xs[i].t, dest->xs[i].object);
		saved = i;
		i = -1;
		while (++i < new.count)
		{
			r.xs[saved] = new.xs[i];
			saved++;
		}
		if (dest->count > 0)
			free(dest->xs);
		return (r);
	}
	return (*dest);
}
