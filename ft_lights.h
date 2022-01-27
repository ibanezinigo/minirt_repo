/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lights.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:00:55 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 16:09:12 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIGHTS_H
# define FT_LIGHTS_H

#include "ft_definitions.h"
# include "ft_tuples.h"



t_light	ft_point_light(t_tuple position, t_color intensity);

#endif