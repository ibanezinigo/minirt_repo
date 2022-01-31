/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tuples_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:21:26 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:25:38 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tuples.h"

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
