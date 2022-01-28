/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinders.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:39:10 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/28 19:22:44 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_CYLINDERS_H
# define FT_CYLINDERS_H

# include "ft_shapes.h"
# include "ft_intersections.h"
# include "ft_rays.h"
# include <math.h>

t_shape			ft_cylinder();
t_intersections	ft_cylinders_intersect(t_shape plane, t_ray ray);
t_tuple			ft_normal_at_cylinder(t_shape cylinder, t_tuple point);

#endif