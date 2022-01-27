/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_materials.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:02:12 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 16:43:50 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATERIALS_H
# define FT_MATERIALS_H

#include "ft_definitions.h"
# include "ft_tuples.h"
# include "ft_patterns.h"



# include "ft_lights.h"
# include <math.h>

t_material  ft_material();
t_color	ft_lighting(t_material material, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv, int in_shadow);
#endif