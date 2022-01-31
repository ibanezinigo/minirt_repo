/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tuples_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:22:06 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:25:44 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tuples.h"

t_color	ft_color_multiply_bycolor(t_color c1, t_color c2)
{
	t_color	color;

	color.red = c1.red * c2.red;
	color.green = c1.green * c2.green;
	color.blue = c1.blue * c2.blue;
	return (color);
}
