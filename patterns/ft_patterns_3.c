/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patterns_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:52:58 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 15:53:06 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_patterns.h"

void	ft_set_pattern_transform(t_pattern s, t_matrix translation)
{
	size_t	x;
	size_t	y;

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
