/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lights.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:01:42 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/28 20:12:28 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lights.h"

t_light	ft_point_light(t_tuple position, t_color intensity)
{
	t_light	light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}
