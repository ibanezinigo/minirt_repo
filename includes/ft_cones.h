/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cones.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:10:33 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 17:42:08 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONES_H
# define FT_CONES_H

# include "ft_shapes.h"
# include "ft_intersections.h"
# include "ft_rays.h"
# include <math.h>
# include "ft_utils.h"

t_shape			ft_cone(void);
t_intersections	ft_cones_intersect(t_shape plane, t_ray ray);
t_tuple			ft_normal_at_cone(t_shape cone, t_tuple point);
t_intersections	ft_intersect_caps_2(t_shape cone,
					t_ray ray, t_intersections inter);
t_intersections	ft_void_inter_2(void);
t_intersections	ft_cones_aux(t_shape cone, t_ray ray, float t0, float t1);

#endif