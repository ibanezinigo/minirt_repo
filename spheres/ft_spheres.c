/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spheres.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:52:36 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 15:44:50 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spheres.h"

t_shape	ft_create_sphere(void)
{
	t_shape	s;

	s.transform = ft_matrix_translation(0, 0, 0);
	s.material = ft_material();
	s.shape_type = 1;
	return (s);
}

t_shape	ft_create_sphere_translated(t_matrix translation)
{
	t_shape	s;

	s.transform = ft_matrix_translation(translation.data[0][3],
			translation.data[1][3], translation.data[2][3]);
	return (s);
}

t_tuple	ft_reflect(t_tuple in, t_tuple normal)
{
	t_tuple	reflection;

	reflection = ft_multiply_tuple(ft_multiply_tuple(normal, 2),
			ft_tuple_dot(in, normal));
	reflection = ft_subtract_tuples(in, reflection);
	return (reflection);
}

t_tuple	ft_normal_at_sphere(t_tuple object_point)
{
	t_tuple	object_normal;

	object_normal = ft_subtract_tuples(object_point, ft_create_point(0, 0, 0));
	return (object_normal);
}
