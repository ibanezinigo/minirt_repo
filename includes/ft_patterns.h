/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patterns.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:26:31 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/28 12:39:49 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PATTERNS_H
# define FT_PATTERNS_H
# include "ft_definitions.h"
# include "ft_tuples.h"
# include "ft_matrices.h"
# include <math.h>

t_pattern	ft_stripe_pattern(t_color a, t_color b);
t_color		ft_stripe_at(t_pattern p, t_tuple point);
t_color		ft_stripe_at_object(t_pattern pattern, t_shape s,
				t_tuple world_point);
void		ft_set_pattern_transform(t_pattern s, t_matrix translation);

#endif