/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shapes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:49:40 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 19:23:35 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHAPES_H
# define FT_SHAPES_H

# include "ft_definitions.h"
# include "ft_matrices.h"

typedef struct s_shape
{
	t_matrix	transform;
}	t_shape;

#endif