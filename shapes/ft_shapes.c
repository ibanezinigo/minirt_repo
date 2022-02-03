/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shapes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:50:12 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 15:44:25 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shapes.h"

t_shape	ft_test_shape(void)
{
	t_shape	shape;

	shape.transform = ft_identity_matrix();
	shape.material = ft_material();
	shape.shape_type = 1;
	return (shape);
}

void	ft_set_transform(t_shape *s, t_matrix translation)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < s->transform.rows && y < translation.rows)
	{
		x = 0;
		while (x < s->transform.cols && y < translation.cols)
		{
			s->transform.data[y][x] = translation.data[y][x];
			x++;
		}
		y++;
	}
}

t_intersections	ft_intersect(t_shape *shape, t_ray ray)
{
	t_intersections	xs;

	shape->saved_ray = ft_ray_transform(ray, ft_inverse(shape->transform));
	if (shape->shape_type == 1)
		xs = ft_sphere_intersect(*shape, shape->saved_ray);
	else if (shape->shape_type == 2)
		xs = ft_plane_intersect(*shape, shape->saved_ray);
	else if (shape->shape_type == 3)
		xs = ft_cylinders_intersect(*shape, shape->saved_ray);
	else if (shape->shape_type == 4)
		xs = ft_cones_intersect(*shape, shape->saved_ray);
	else
		xs = ft_sphere_intersect(*shape, shape->saved_ray);
	return (xs);
}

t_tuple	ft_normal_at(t_shape s, t_tuple t)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;
	t_tuple	result;

	object_point = ft_multiply_matrix_tuple(ft_inverse(s.transform), t);
	if (s.shape_type == 1)
		object_normal = ft_normal_at_sphere(object_point);
	else if (s.shape_type == 2)
		object_normal = ft_normal_at_plane();
	else if (s.shape_type == 3)
		object_normal = ft_normal_at_cylinder(s, object_point);
	else if (s.shape_type == 4)
		object_normal = ft_normal_at_cone(s, object_point);
	else
	{
		printf("Error at ft_normal_at -> no shape type defined\n");
		object_normal = ft_normal_at_sphere(object_point);
	}
	world_normal = ft_multiply_matrix_tuple(
			ft_matrix_transpose(ft_inverse(s.transform)), object_normal);
	world_normal.w = 0;
	result = ft_tuple_normalize(world_normal);
	return (result);
}
