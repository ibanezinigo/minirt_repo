/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrices_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:27:15 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 15:42:08 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrices.h"

void	ft_print_matrix(t_matrix m)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < m.rows)
	{
		x = 0;
		while (x < m.cols)
		{
			printf("%f\t", m.data[y][x]);
			x++;
		}
		y++;
		printf("\n");
	}
}
