/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrices_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:26:15 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:28:40 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrices.h"

t_matrix	ft_submatrix(t_matrix m, size_t row, size_t col)
{
	t_matrix	matrix;
	size_t		i;
	size_t		j;
	size_t		r;
	size_t		c;

	matrix = ft_matrix(m.rows - 1, m.cols - 1);
	r = 0;
	c = 0;
	i = 0;
	while (i < m.rows)
	{
		j = 0;
		c = 0;
		while (j < m.cols)
		{
			if (i != row && j != col)
			{
				matrix.data[r][c] = m.data[i][j];
				c++;
			}
			j++;
		}
		if (i != row)
			r++;
		i++;
	}
	return (matrix);
}

float	ft_minor(t_matrix m, size_t row, size_t col)
{
	t_matrix	matrix;
	float		result;

	matrix = ft_submatrix(m, row, col);
	result = ft_determinant(matrix);
	return (result);
}

float	ft_cofactor(t_matrix m, size_t row, size_t col)
{
	float	result;

	result = ft_minor(m, row, col);
	if (((row + col) % 2) != 0)
	{
		result = result * -1;
	}
	return (result);
}

float	ft_determinant(t_matrix m)
{
	int		i;
	float	result;

	result = 0;
	if (m.rows == 2)
	{
		result = m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
		return (result);
	}
	i = 0;
	while (i < m.cols)
	{
		result += m.data[0][i] * ft_cofactor(m, 0, i);
		i++;
	}
	return (result);
}

t_matrix	ft_inverse(t_matrix m)
{
	float		det;
	t_matrix	matrix;
	size_t		r;
	size_t		c;

	det = ft_determinant(m);
	matrix = ft_matrix(m.rows, m.cols);
	r = 0;
	while (r < m.rows)
	{
		c = 0;
		while (c < m.cols)
		{
			matrix.data[c][r] = ft_cofactor(m, r, c) / det;
			c++;
		}
		r++;
	}
	return (matrix);
}
