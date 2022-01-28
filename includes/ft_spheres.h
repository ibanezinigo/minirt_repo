/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spheres.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:51:59 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/28 13:34:33 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPHERES_H
# define FT_SPHERES_H

# include "ft_definitions.h"
# include "ft_materials.h"
# include "ft_matrices.h"
# include "ft_tuples.h"
# include <stdio.h>
# include "ft_transformations.h"

t_shape		ft_create_sphere(void);
t_shape		ft_create_sphere_translated(t_matrix translation);
t_tuple		ft_normal_at_sphere(t_shape s, t_tuple object_point);
t_tuple		ft_reflect(t_tuple in, t_tuple normal);

#endif