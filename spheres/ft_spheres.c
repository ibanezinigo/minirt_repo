/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spheres.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:52:36 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 19:13:24 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spheres.h"

t_sphere	ft_create_sphere(void)
{
	t_sphere	s;

	s.origin = ft_create_point(0, 0, 0);
	s.radius = 1;
	s.transform = ft_matrix_translation(0, 0, 0);
	s.material = ft_material();
	return (s);
}

t_sphere	ft_create_sphere_translated(t_matrix translation)
{
	t_sphere	s;

	s.origin = ft_create_point(0, 0, 0);
	s.radius = 1;
	s.transform = ft_matrix_translation(translation.data[0][3],
			translation.data[1][3], translation.data[2][3]);
	return (s);
}

void	ft_sphere_set_transform(t_sphere s, t_matrix translation)
{
	int	x;
	int	y;

	y = 0;
	while (y < s.transform.rows && y < translation.rows)
	{
		x = 0;
		while (x < s.transform.cols && y < translation.cols)
		{
			s.transform.data[y][x] = translation.data[y][x];
			x++;
		}
		y++;
	}
}

t_tuple	ft_normal_at(t_shape s, t_tuple t)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;
	t_tuple	result;

	object_point = ft_multiply_matrix_tuple(ft_inverse(s.transform), t);
	object_normal = ft_subtract_tuples(object_point, ft_create_point(0, 0, 0));
	world_normal = ft_multiply_matrix_tuple(
			ft_matrix_transpose(ft_inverse(s.transform)), object_normal);
	world_normal.w = 0;
	result = ft_tuple_normalize(world_normal);
	return (result);
}

t_tuple	ft_reflect(t_tuple in, t_tuple normal)
{
	t_tuple	reflection;

	reflection = ft_multiply_tuple(ft_multiply_tuple(normal, 2),
			ft_tuple_dot(in, normal));
	reflection = ft_subtract_tuples(in, reflection);
	return (reflection);
}

void	ft_sphere_print(t_sphere s)
{
	int	x;
	int	y;

	printf("origin->\t%f\t%f\t%f\t%f\n", s.origin.x, s.origin.y,
		s.origin.z, s.origin.w);
	printf("color->\t\t%f\t%f\t%f\n", s.material.color.red,
		s.material.color.green, s.material.color.blue);
	printf("ambient->\t%f\n", s.material.ambient);
	printf("diffuse->\t%f\n", s.material.diffuse);
	printf("shininess->\t%f\n", s.material.shininess);
	printf("specular->\t%f\n", s.material.specular);
	printf("transform->\n");
	y = 0;
	while (y < s.transform.rows)
	{
		x = 0;
		while (x < s.transform.cols)
		{
			printf("%f ", s.transform.data[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("_________________________\n");
}
