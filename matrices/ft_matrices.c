/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:04:04 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:26:34 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrices.h"
#include "ft_tuples.h"

t_matrix	ft_matrix(size_t r, size_t c)
{
	t_matrix	m;
	size_t		i;
	size_t		j;

	m.rows = r;
	m.cols = c;
	i = 0;
	while (i < m.rows)
	{
		j = 0;
		while (j < m.cols)
		{
			m.data[i][j] = 0;
			j++;
		}
		i++;
	}
	return (m);
}

t_matrix	ft_identity_matrix(void)
{
	t_matrix	m;

	m = ft_matrix(4, 4);
	m.data[0][0] = 1;
	m.data[1][1] = 1;
	m.data[2][2] = 1;
	m.data[3][3] = 1;
	return (m);
}

int	ft_matrix_equals(t_matrix m1, t_matrix m2)
{
	size_t	i;
	size_t	j;

	if (m1.cols != m2.cols || m1.rows != m2.rows)
		return (0);
	i = 0;
	while (i < m1.rows)
	{
		j = 0;
		while (j < m1.cols)
		{
			if (m1.data[i][j] != m2.data[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_matrix	ft_matrix_multiply(t_matrix m1, t_matrix m2)
{
	t_matrix	m;
	size_t		i;
	size_t		j;
	size_t		k;

	m = ft_matrix(m1.rows, m2.cols);
	i = 0;
	while (i < m1.rows)
	{
		j = 0;
		while (j < m2.cols)
		{
			m.data[i][j] = 0;
			k = 0;
			while (k < m1.cols)
			{
				m.data[i][j] += m1.data[i][k] * m2.data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (m);
}

t_matrix	ft_matrix_transpose(t_matrix m)
{
	t_matrix	m2;
	size_t		i;
	size_t		j;

	m2 = ft_matrix(m.cols, m.rows);
	i = 0;
	while (i < m.rows)
	{
		j = 0;
		while (j < m.cols)
		{
			m2.data[j][i] = m.data[i][j];
			j++;
		}
		i++;
	}
	return (m2);
}
