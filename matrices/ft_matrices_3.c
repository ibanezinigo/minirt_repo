/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrices_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:27:15 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:28:09 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrices.h"

void	ft_print_matrix(t_matrix m)
{
	int	x;
	int	y;

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
