/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:50:50 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/26 11:51:36 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rays.h"

t_ray   ft_ray(t_tuple origin, t_tuple direction)
{
	t_ray   ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_tuple ft_ray_position(t_ray ray, float t)
{
	return (ft_add_tuples(ray.origin, ft_multiply_tuple(ray.direction, t)));
}