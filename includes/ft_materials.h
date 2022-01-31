/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_materials.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:02:12 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 12:54:30 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATERIALS_H
# define FT_MATERIALS_H

# include "ft_definitions.h"
# include "ft_tuples.h"
# include "ft_patterns.h"
# include "ft_lights.h"
# include <math.h>

t_material	ft_material(void);
t_color		ft_lighting(t_shape shape, t_material material, t_light light, t_tuple point,
				t_tuple eyev, t_tuple normalv, int in_shadow);
#endif