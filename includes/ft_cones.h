/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cones.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:10:33 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 16:18:28 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONES_H
# define FT_CONES_H

# include "ft_shapes.h"
# include "ft_intersections.h"
# include "ft_rays.h"
# include <math.h>

t_shape			ft_cone(void);
t_intersections	ft_cones_intersect(t_shape plane, t_ray ray);
t_tuple			ft_normal_at_cone(t_shape cone, t_tuple point);

#endif