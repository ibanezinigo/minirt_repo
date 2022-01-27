/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tuples.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:36:29 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 19:47:10 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TUPLES_H
# define FT_TUPLES_H

# include "ft_definitions.h"
# include "math.h"

t_tuple	ft_create_vector(float x, float y, float z);
t_tuple	ft_create_point(float x, float y, float z);
t_tuple	ft_add_tuples(t_tuple t1, t_tuple t2);
t_tuple	ft_subtract_tuples(t_tuple t1, t_tuple t2);
t_tuple	ft_multiply_tuple(t_tuple t1, float s);
t_tuple	ft_divide_tuple(t_tuple t1, float s);
t_tuple	ft_negate_tuple(t_tuple t1);
float	ft_tuple_magnitude(t_tuple t);
t_tuple	ft_tuple_normalize(t_tuple t);
float	ft_tuple_dot(t_tuple t1, t_tuple t2);
t_tuple	ft_tuple_cross(t_tuple t1, t_tuple t2);
t_color	ft_color(float r, float g, float b);
t_color	ft_color_add(t_color c1, t_color c2);
t_color	ft_color_subtract(t_color c1, t_color c2);
t_color	ft_color_multiply_byscalar(t_color c1, float s);
t_color	ft_color_multiply_bycolor(t_color c1, t_color c2);

#endif