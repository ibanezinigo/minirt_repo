/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:50:21 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/26 12:05:41 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RAYS_H
# define FT_RAYS_H
# include "ft_tuples.h"

typedef struct s_ray
{
	t_tuple origin;
	t_tuple direction;
}   t_ray;

t_ray	ft_ray(t_tuple origin, t_tuple direction);
t_tuple	ft_ray_position(t_ray ray, float t);

#endif