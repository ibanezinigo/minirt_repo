/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_world_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:25:07 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 13:49:20 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_world.h"

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