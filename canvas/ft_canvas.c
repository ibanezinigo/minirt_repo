/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_canvas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:03:43 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:11:44 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_canvas.h"

void	ft_free_canvas(t_canvas c)
{
	int	i;

	i = 0;
	while (i < c.height)
	{
		free(c.pixel[i]);
		i++;
	}
	free(c.pixel);
}

t_canvas	ft_canvas(size_t w, size_t h)
{
	t_canvas	canvas;
	int			i;
	int			j;

	canvas.width = w;
	canvas.height = h;
	canvas.pixel = malloc(sizeof(t_color *) * canvas.height);
	i = -1;
	while (++i < canvas.height)
		canvas.pixel[i] = malloc(sizeof(t_color) * canvas.width);
	i = -1;
	while (++i < canvas.height)
	{
		j = -1;
		while (++j < canvas.width)
		{
			canvas.pixel[i][j].red = 0;
			canvas.pixel[i][j].green = 0;
			canvas.pixel[i][j].blue = 0;
		}
	}
	return (canvas);
}

void	ft_write_pixel(t_canvas canvas, size_t x, size_t y, t_color color)
{
	if (x >= canvas.width || x < 0)
	{
		printf("error x\n");
		return ;
	}
	if (y >= canvas.height || y < 0)
	{
		printf("error y\n");
		return ;
	}
	canvas.pixel[y][x].red = color.red;
	canvas.pixel[y][x].green = color.green;
	canvas.pixel[y][x].blue = color.blue;
}

void	ft_read_pixel(FILE *f, t_canvas canvas, size_t x, size_t y)
{
	if (canvas.pixel[y][x].red < 0)
		fprintf(f, "0 ");
	else if (canvas.pixel[y][x].red > 1)
		fprintf(f, "255 ");
	else
		fprintf(f, "%i ", (int)(canvas.pixel[y][x].red * 255));
	if (canvas.pixel[y][x].green < 0)
		fprintf(f, "0 ");
	else if (canvas.pixel[y][x].green > 1)
		fprintf(f, "255 ");
	else
		fprintf(f, "%i ", (int)(canvas.pixel[y][x].green * 255));
	if (canvas.pixel[y][x].blue < 0)
		fprintf(f, "0");
	else if (canvas.pixel[y][x].blue > 1)
		fprintf(f, "255");
	else
		fprintf(f, "%i", (int)(canvas.pixel[y][x].blue * 255));
}

void	ft_canvas_to_ppm(t_canvas c)
{
	FILE	*f;
	int		w;
	int		h;
	int		total;

	f = fopen("test.ppm", "w+");
	fprintf(f, "P3\n");
	fprintf(f, "%zu %zu\n", c.width, c.height);
	fprintf(f, "255\n");
	h = -1;
	total = 0;
	while (++h < c.height)
	{
		w = -1;
		while (++w < c.width)
		{
			ft_read_pixel(f, c, w, h);
			if (w < (c.width - 1))
				fprintf(f, " ");
			if ((total + 1) % 5 == 0)
				fprintf(f, "\n");
			total++;
		}
	}
	fclose(f);
}
