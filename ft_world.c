/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_world.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:36:01 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/26 19:54:59 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_world.h"

t_world ft_world()
{
    t_world world;

    world.n_lights = 0;
    world.n_spheres = 0;
    world.lights = NULL;
    world.spheres = NULL;
    return (world);
}

t_intersections ft_intersect_world(t_world world, t_ray ray)
{
    t_intersections xs;
    t_intersections tmp;
    t_intersection  inter;
    int             i;
    int             j;

    xs.count = 0;
    i = 0;
    while (i < world.n_spheres)
    {
        tmp = ft_intersect(world.spheres[i], ray);
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

t_color ft_shade_hit(t_world w, t_comps c)
{
    t_color result;
    int     i;

    result = ft_color(0, 0, 0);
    i = 0;
    while (i < w.n_lights)
    {
        printf("%i\n",i);
        result = ft_color_add(result, ft_lighting(c.object.material, w.lights[i], c.point, c.eyev, c.normalv));
        i++;
    }
    return (result);
}

t_color ft_color_at(t_world w, t_ray r)
{
    t_intersections inter;
    t_intersection  hit;
    t_comps         c;

    inter = ft_intersect_world(w, r);
    hit = ft_hit(inter);
    if (hit.t < 0)
        return (ft_color(0, 0, 0));
    else
    {
        c = ft_prepare_computations(hit, r);
        return (ft_shade_hit(w, c));
    }
}




t_world ft_world_add_light(t_world world, t_light newlight)
{
    t_world newworld;
    int     i;

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

t_world ft_world_add_sphere(t_world world, t_sphere sphere)
{
    t_world newworld;
    int     i;

    newworld.n_lights = world.n_lights;
    newworld.lights = world.lights;
    newworld.n_spheres = world.n_spheres + 1;
    i = 0;
    newworld.spheres = malloc(sizeof(t_sphere) * newworld.n_spheres);
    while (i < world.n_spheres)
    {
        newworld.spheres[i] = (t_sphere)world.spheres[i];
        i++;
    }
    newworld.spheres[i] = sphere;
    if (world.n_spheres > 0)
        free(world.spheres);
    return (newworld);
}