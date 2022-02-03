/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_world.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:36:01 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 19:47:34 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_world.h"

t_world	ft_world(void)
{
	t_world	world;

	world.n_lights = 0;
	world.n_spheres = 0;
	world.lights = NULL;
	world.spheres = NULL;
	return (world);
}

t_world	ft_default_world(void)
{
	t_world		w;
	t_light		ligth;
	t_shape		s1;
	t_shape		s2;

	ligth = ft_point_light(ft_create_point(-10, 10, -10), ft_color(1, 1, 1));
	s1 = ft_create_sphere();
	s1.material.color = ft_color(0.8, 1, 0.6);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.2;
	s2 = ft_create_sphere();
	s2.transform = ft_matrix_scaling(0.5, 0.5, 0.5);
	w = ft_world();
	w = ft_world_add_light(w, ligth);
	w = ft_world_add_sphere(w, s1);
	w = ft_world_add_sphere(w, s2);
	return (w);
}

void	ft_order_intersects(t_intersections *xs)
{
	int				i;
	int				j;
	t_intersection	inter;

	i = -1;
	while (++i < xs->count)
	{
		j = i;
		while (++j < xs->count)
		{
			if (xs->xs[j].t < xs->xs[i].t)
			{
				inter = xs->xs[j];
				xs->xs[j] = xs->xs[i];
				xs->xs[i] = inter;
			}
		}
	}
}

t_intersections	ft_intersect_world(t_world world, t_ray ray)
{
	t_intersections	xs;
	t_intersections	tmp;
	int				i;

	xs.count = 0;
	i = -1;
	while (++i < world.n_spheres)
	{
		tmp = ft_intersect(&world.spheres[i], ray);
		xs = ft_add_intersections(&xs, tmp);
		if (tmp.count > 0)
			free(tmp.xs);
	}
	ft_order_intersects(&xs);
	return (xs);
}

t_color	ft_shade_hit(t_shape shape, t_world w, t_comps c)
{
	t_color	result;
	int		is_shadowed;
	int		i;

	result = ft_color(0, 0, 0);
	i = 0;
	while (i < w.n_lights)
	{
		is_shadowed = ft_is_shadowed(w, c.over_point);
		result = ft_color_add(result, ft_lighting(shape,
					c, w.lights[i], is_shadowed));
		i++;
	}
	return (result);
}
