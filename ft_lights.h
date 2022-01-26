/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lights.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:00:55 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/26 12:44:29 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIGHTS_H
# define FT_LIGHTS_H

# include "ft_tuples.h"

typedef struct s_light
{
	t_tuple	position;
	t_color	intensity;
}	t_light;

t_light	ft_point_light(t_tuple position, t_color intensity);

#endif