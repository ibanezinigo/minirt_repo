/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrices.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:05:46 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 19:06:07 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATRICES_H
# define FT_MATRICES_H

# include "ft_definitions.h"
# include <stdlib.h>

t_matrix	ft_matrix(size_t r, size_t c);
t_matrix	ft_identity_matrix(void);
void		ft_matrix_free_data(t_matrix m);
int			ft_matrix_equals(t_matrix m1, t_matrix m2);
t_matrix	ft_matrix_multiply(t_matrix m1, t_matrix m2);
t_matrix	ft_matrix_transpose(t_matrix m);
t_matrix	ft_submatrix(t_matrix m, size_t row, size_t col);
float		ft_minor(t_matrix m, size_t row, size_t col);
float		ft_cofactor(t_matrix m, size_t row, size_t col);
float		ft_determinant(t_matrix m);
t_matrix	ft_inverse(t_matrix m);

#endif