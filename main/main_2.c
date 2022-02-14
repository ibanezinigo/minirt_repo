/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:34:22 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/14 16:37:59 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_definitions.h"
#include "../.minilibx/mlx.h"

void	my_mlx_pixel_put(t_info *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	ft_convert_color(t_color c)
{
	int	value;

	value = 0;
	if (c.red > 1)
		value = value + 255 * 256 * 256;
	else if (c.red > 0)
		value = value + ((int)(c.red * 255)) * 256 * 256;
	if (c.green > 1)
		value = value + 255 * 256;
	else if (c.green > 0)
		value = value + ((int)(c.green * 255)) * 256;
	if (c.blue > 1)
		value = value + 255;
	else if (c.blue > 0)
		value = value + ((int)(c.blue * 255));
	return (value);
}

void	ft_draw(t_info *vars, t_canvas canvas)
{
	int		x;
	int		y;
	int		color;

	x = 0;
	while (x < vars->width)
	{
		y = 0;
		while (y < vars->height)
		{
			color = ft_convert_color(canvas.pixel[y][x]);
			my_mlx_pixel_put(vars, x, y, color);
			y++;
		}
		x++;
	}
}

int	close_win(int keycode, t_info *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		exit(0);
	}
	return (0);
}

int	close_win_2(int keycode, t_info *vars)
{
	vars = NULL;
	keycode = 0;
	exit(0);
	return (0);
}
