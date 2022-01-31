/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersections.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:53:34 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:18:54 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INTERSECTIONS_H
# define FT_INTERSECTIONS_H

# include "ft_definitions.h"
# include "ft_spheres.h"
# include "ft_rays.h"
# include "ft_tuples.h"
# include "ft_shapes.h"

t_intersections	ft_sphere_intersect(t_shape s, t_ray r);
t_intersection	ft_intersection(float t, t_shape s);
t_intersections	ft_intersections(t_intersections base, t_intersection inter);
t_intersection	ft_hit(t_intersections inter);
t_intersections	ft_add_intersections(t_intersections *dest,
					t_intersections new);
t_comps			ft_prepare_computations(t_intersection inter, t_ray ray);

#endif