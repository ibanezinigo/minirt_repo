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
	return (shape);
}
