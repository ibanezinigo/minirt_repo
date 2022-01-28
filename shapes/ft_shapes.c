/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shapes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:50:12 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 19:28:47 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shapes.h"

t_shape	ft_test_shape(void)
{
	t_shape	shape;

	shape.transform = ft_identity_matrix();
	shape.material = ft_material();
	return (shape);
}

void	ft_set_transform(t_shape s, t_matrix translation)
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

t_intersections	ft_intersect(t_shape shape, t_ray ray)
{
	t_ray			local_ray;

	local_ray = ft_ray_transform(ray, ft_inverse(shape.transform));
	return (ft_intersect(shape, local_ray));
}