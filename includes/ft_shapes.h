/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shapes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:49:40 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 19:23:35 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHAPES_H
# define FT_SHAPES_H

# include "ft_definitions.h"
# include "ft_matrices.h"
# include "ft_materials.h"
# include "ft_transformations.h"
# include "ft_spheres.h"

t_shape	ft_test_shape(void);
void	ft_set_transform(t_shape s, t_matrix translation);
t_intersections	ft_intersect(t_shape shape, t_ray ray);

#endif