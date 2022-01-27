/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tuples.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:04:39 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 19:42:04 by iibanez-         ###   ########.fr       */
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

t_tuple	ft_divide_tuple(t_tuple t1, float s)
{
	return (ft_multiply_tuple(t1, 1 / s));
}

t_tuple	ft_negate_tuple(t_tuple t1)
{
	return (ft_multiply_tuple(t1, -1));
}

float	ft_tuple_magnitude(t_tuple t)
{
	float	result;

	result = 0;
	result += pow(t.x, 2);
	result += pow(t.y, 2);
	result += pow(t.z, 2);
	result += pow(t.w, 2);
	result = sqrt(result);
	return (result);
}

t_tuple	ft_tuple_normalize(t_tuple t)
{
	float	magnitude;

	magnitude = ft_tuple_magnitude(t);
	return (ft_divide_tuple(t, magnitude));
}

float	ft_tuple_dot(t_tuple t1, t_tuple t2)
{
	float	r;

	r = 0;
	r += t1.x * t2.x;
	r += t1.y * t2.y;
	r += t1.z * t2.z;
	r += t1.w * t2.w;
	return (r);
}

t_tuple	ft_tuple_cross(t_tuple t1, t_tuple t2)
{
	t_tuple	t;

	t.x = t1.y * t2.z - t1.z * t2.y;
	t.y = t1.z * t2.x - t1.x * t2.z;
	t.z = t1.x * t2.y - t1.y * t2.x;
	t.w = t1.w * t2.w - t1.w * t2.w;
	return (t);
}

t_color	ft_color(float r, float g, float b)
{
	t_color	color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

t_color	ft_color_add(t_color c1, t_color c2)
{
	t_color	color;

	color.red = c1.red + c2.red;
	color.green = c1.green + c2.green;
	color.blue = c1.blue + c2.blue;
	return (color);
}

t_color	ft_color_subtract(t_color c1, t_color c2)
{
	t_color	color;

	color.red = c1.red - c2.red;
	color.green = c1.green - c2.green;
	color.blue = c1.blue - c2.blue;
	return (color);
}

t_color	ft_color_multiply_byscalar(t_color c1, float s)
{
	t_color	color;

	color.red = c1.red * s;
	color.green = c1.green * s;
	color.blue = c1.blue * s;
	return (color);
}

t_color	ft_color_multiply_bycolor(t_color c1, t_color c2)
{
	t_color	color;

	color.red = c1.red * c2.red;
	color.green = c1.green * c2.green;
	color.blue = c1.blue * c2.blue;
	return (color);
}
