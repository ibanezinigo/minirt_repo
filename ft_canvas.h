#ifndef FT_CANVAS_H
# define FT_CANVAS_H

# include "ft_tuples.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_canvas
{
	size_t  width;
	size_t  height;
	t_color **pixel;
}   t_canvas;

t_canvas	ft_canvas(size_t w, size_t h);
void		ft_write_pixel(t_canvas canvas, size_t x, size_t y, t_color color);
void		ft_read_pixel(FILE *f, t_canvas canvas, size_t x, size_t y);
void		ft_canvas_to_ppm(t_canvas c);
#endif