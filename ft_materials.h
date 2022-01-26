/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_materials.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:02:12 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/26 13:15:20 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATERIALS_H
# define FT_MATERIALS_H

# include "ft_tuples.h"

typedef	struct s_material
{
	t_color	color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
} t_material;

# include "ft_lights.h"
# include "ft_spheres.h"
# include <math.h>

t_material  ft_material();
t_color		ft_lighting (t_material material, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv);
#endif