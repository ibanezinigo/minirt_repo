/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_world.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:35:58 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/08 18:09:36 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WORLD_H
# define FT_WORLD_H

# include "ft_definitions.h"
# include "ft_spheres.h"
# include "ft_lights.h"
# include "ft_intersections.h"
# include <stdlib.h>

t_world			ft_world(void);
t_world			ft_default_world(void);
t_intersections	ft_intersect_world(t_world world, t_ray ray);
t_world			ft_world_add_light(t_world world, t_light newlight);
t_world			ft_world_add_sphere(t_world world, t_shape sphere);
t_color			ft_shade_hit(t_shape shape, t_world w, t_comps c);
t_color			ft_color_at(t_world w, t_ray r);
int				ft_is_shadowed(t_world world, t_tuple point, int i);

#endif