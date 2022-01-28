/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_world.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:36:01 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/28 20:14:21 by iibanez-         ###   ########.fr       */
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

t_intersections	ft_intersect_world(t_world world, t_ray ray)
{
	t_intersections	xs;
	t_intersections	tmp;
	t_intersection	inter;
	int				i;
	int				j;

	xs.count = 0;
	i = 0;
	while (i < world.n_spheres)
	{
		tmp = ft_intersect(&world.spheres[i], ray);
		xs = ft_add_intersections(xs, tmp);
		i++;
	}
	i = 0;
	while (i < xs.count)
	{
		j = i + 1;
		while (j < xs.count)
		{
			if (xs.xs[j].t < xs.xs[i].t)
			{
				inter = xs.xs[j];
				xs.xs[j] = xs.xs[i];
				xs.xs[i] = inter;
			}
			j++;
		}
		i++;
	}
	return (xs);
}

t_color	ft_shade_hit(t_world w, t_comps c)
{
	t_color	result;
	int		is_shadowed;
	int		i;

	result = ft_color(0, 0, 0);
	i = 0;
	while (i < w.n_lights)
	{
		is_shadowed = ft_is_shadowed(w, c.over_point);
		result = ft_color_add(result, ft_lighting(c.object.material,
					w.lights[i], c.over_point, c.eyev, c.normalv, is_shadowed));
		i++;
	}
	return (result);
}

t_color	ft_color_at(t_world w, t_ray r)
{
	t_intersections	inter;
	t_intersection	hit;
	t_comps			c;

	inter = ft_intersect_world(w, r);
	hit = ft_hit(inter);
	if (inter.count > 0)
		free(inter.xs);
	if (hit.t < 0)
		return (ft_color(0, 0, 0));
	else
	{
		c = ft_prepare_computations(hit, r);
		return (ft_shade_hit(w, c));
	}
}

t_world	ft_world_add_light(t_world world, t_light newlight)
{
	t_world	newworld;
	int		i;

	newworld.n_spheres = world.n_spheres;
	newworld.spheres = world.spheres;
	newworld.n_lights = world.n_lights + 1;
	i = 0;
	newworld.lights = malloc(sizeof(t_light) * newworld.n_lights);
	while (i < world.n_lights)
	{
		newworld.lights[i] = (t_light) world.lights[i];
		i++;
	}
	newworld.lights[i] = newlight;
	if (world.n_lights > 0)
		free(world.lights);
	return (newworld);
}

t_world	ft_world_add_sphere(t_world world, t_shape sphere)
{
	t_world	newworld;
	int		i;

	newworld.n_lights = world.n_lights;
	newworld.lights = world.lights;
	newworld.n_spheres = world.n_spheres + 1;
	i = 0;
	newworld.spheres = malloc(sizeof(t_shape) * newworld.n_spheres);
	while (i < world.n_spheres)
	{
		newworld.spheres[i] = world.spheres[i];
		i++;
	}
	newworld.spheres[i] = sphere;
	if (world.n_spheres > 0)
		free(world.spheres);
	return (newworld);
}

int	ft_is_shadowed(t_world world, t_tuple point)
{
	t_tuple			v;
	float			distance;
	t_tuple			direction;
	t_ray			ray;
	t_intersections	intersections;
	t_intersection	hit;

	v = ft_subtract_tuples(world.lights[0].position, point);
	distance = ft_tuple_magnitude(v);
	direction = ft_tuple_normalize(v);
	ray = ft_ray(point, direction);
	intersections = ft_intersect_world(world, ray);
	hit = ft_hit(intersections);
	if (intersections.count > 0)
		free(intersections.xs);
	if (hit.t != -1 && hit.t < distance)
		return (1);
	else
		return (0);
}
