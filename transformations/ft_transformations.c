/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transformations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:04:32 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:23:41 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_transformations.h"

t_matrix	ft_matrix_translation(float x, float y, float z)
{
	t_matrix	trans;

	trans = ft_matrix(4, 4);
	trans.data[0][0] = 1;
	trans.data[1][1] = 1;
	trans.data[2][2] = 1;
	trans.data[3][3] = 1;
	trans.data[0][3] = x;
	trans.data[1][3] = y;
	trans.data[2][3] = z;
	return (trans);
}

t_matrix	ft_matrix_scaling(float x, float y, float z)
{
	t_matrix	trans;

	trans = ft_matrix(4, 4);
	trans.data[0][0] = x;
	trans.data[1][1] = y;
	trans.data[2][2] = z;
	trans.data[3][3] = 1;
	return (trans);
}

t_matrix	ft_matrix_rotation_x(float x)
{
	t_matrix	m;

	m = ft_matrix(4, 4);
	m.data[0][0] = 1;
	m.data[3][3] = 1;
	m.data[1][1] = cos((double)x);
	m.data[1][2] = sin((double)x) * -1;
	m.data[2][1] = sin((double)x);
	m.data[2][2] = cos((double)x);
	return (m);
}

t_matrix	ft_matrix_rotation_y(float y)
{
	t_matrix	m;

	m = ft_matrix(4, 4);
	m.data[0][0] = cos((double)y);
	m.data[0][2] = sin((double)y);
	m.data[1][1] = 1;
	m.data[2][0] = sin((double)y) * -1;
	m.data[2][2] = cos((double)y);
	m.data[3][3] = 1;
	return (m);
}

t_matrix	ft_matrix_rotation_z(float z)
{
	t_matrix	m;

	m = ft_matrix(4, 4);
	m.data[0][0] = cos((double)z);
	m.data[0][1] = sin((double)z) * -1;
	m.data[1][0] = sin((double)z);
	m.data[1][1] = cos((double)z);
	m.data[2][2] = 1;
	m.data[3][3] = 1;
	return (m);
}
