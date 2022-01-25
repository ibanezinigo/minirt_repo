
#include "ft_matrices.h"
#include "ft_tuples.h"

t_matrix    ft_matrix(size_t r, size_t c)
{
	t_matrix    m;
	size_t      i;
	size_t      j;

	m.rows = r;
	m.cols = c;
	m.data = malloc(sizeof(float *) * m.rows);
	i = 0;
	while (i < m.rows)
	{
		m.data[i] = malloc(sizeof(float) * m.cols);
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

void    ft_matrix_free_data(t_matrix m)
{
	int i;

	i = 0;
	while (i < m.rows)
	{
		free(m.data[i]);
		i++;
	}
	free(m.data);
}

int ft_matrix_equals(t_matrix m1, t_matrix m2)
{
	size_t  i;
	size_t  j;

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

t_matrix ft_matrix_multiply(t_matrix m1, t_matrix m2)
{
	t_matrix    m;
	size_t      i;
	size_t      j;
	size_t      k;

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

t_matrix    ft_matrix_transpose(t_matrix m)
{
	t_matrix    m2;
	size_t      i;
	size_t      j;

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

t_matrix    ft_submatrix(t_matrix m, size_t row, size_t col)
{
	t_matrix    matrix;
	size_t      i;
	size_t      j;
	size_t      r;
	size_t      c;

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


float   ft_minor(t_matrix m, size_t row, size_t col)
{
	t_matrix    matrix;
	float       result;

	matrix = ft_submatrix(m, row, col);
	//printf("size-> %zu %zu\n", m.cols, matrix.cols);
	result = ft_determinant(matrix);
	ft_matrix_free_data(matrix);
	return (result);
}

float   ft_cofactor(t_matrix m, size_t row, size_t col)
{
	float   result;

	result = ft_minor(m, row, col);
	if (((row + col) % 2) != 0)
	{
		result = result * -1;
	}
	return (result);
}

float   ft_determinant(t_matrix m)
{
	int     i;
	float   result;

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

t_matrix    ft_inverse(t_matrix m)
{
	float       det;
	t_matrix    matrix;
	size_t      r;
	size_t      c;

	det = ft_determinant(m);
	matrix = ft_matrix(m.rows, m.cols);
	r = 0;
	while (r < m.rows)
	{
		c = 0;
		while (c < m.cols)
		{
			//Swaped c and r to transpose
			matrix.data[c][r] = ft_cofactor(m, r, c) / det;
			c++;
		}
		r++;
	}
	return (matrix);
}
