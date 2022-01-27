/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_world.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:35:58 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/26 19:53:39 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WORLD_H
# define FT_WORLD_H

#include "ft_spheres.h"
#include "ft_lights.h"
#include "ft_intersections.h"
# include <stdlib.h>

typedef struct  s_world
{
	int			n_lights;
	t_light		*lights;
	int			n_spheres;
	t_sphere	*spheres;

}   t_world;

t_world 		ft_world();
t_world 		ft_default_world();
t_intersections	ft_intersect_world(t_world world, t_ray ray);
t_world 		ft_world_add_light(t_world world, t_light newlight);
t_world 		ft_world_add_sphere(t_world world, t_sphere sphere);
t_color 		ft_shade_hit(t_world w, t_comps c);
t_color 		ft_color_at(t_world w, t_ray r);

#endif