/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_planes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:47:10 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/28 15:23:50 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PLANES_H
# define FT_PLANES_H

# include "ft_tuples.h"
# include "ft_shapes.h"

t_shape			ft_plane(void);
t_tuple			ft_normal_at_plane(void);
t_intersections	ft_plane_intersect(t_shape plane, t_ray ray);
#endif