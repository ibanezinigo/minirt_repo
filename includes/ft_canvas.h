/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_canvas.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:48:34 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/28 20:09:13 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CANVAS_H
# define FT_CANVAS_H

# include "ft_definitions.h"
# include "ft_tuples.h"
# include <stdlib.h>
# include <stdio.h>

t_canvas	ft_canvas(size_t w, size_t h);
void		ft_write_pixel(t_canvas canvas, size_t x, size_t y, t_color color);
void		ft_read_pixel(FILE *f, t_canvas canvas, size_t x, size_t y);
void		ft_canvas_to_ppm(t_canvas c);
void		ft_free_canvas(t_canvas c);

#endif