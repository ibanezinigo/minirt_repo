/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tuples.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:04:39 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:21:16 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tuples.h"

t_tuple	ft_create_vector(float x, float y, float z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = 0;
	return (tuple);
}

t_tuple	ft_create_point(float x, float y, float z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = 1;
	return (tuple);
}

t_tuple	ft_add_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple	tuple;

	tuple.x = t1.x + t2.x;
	tuple.y = t1.y + t2.y;
	tuple.z = t1.z + t2.z;
	tuple.w = t1.w + t2.w;
	return (tuple);
}

t_tuple	ft_subtract_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple	tuple;

	tuple.x = t1.x - t2.x;
	tuple.y = t1.y - t2.y;
	tuple.z = t1.z - t2.z;
	tuple.w = t1.w - t2.w;
	return (tuple);
}

t_tuple	ft_multiply_tuple(t_tuple t1, float s)
{
	t_tuple	tuple;

	tuple.x = t1.x * (s);
	tuple.y = t1.y * (s);
	tuple.z = t1.z * (s);
	tuple.w = t1.w * (s);
	return (tuple);
}
