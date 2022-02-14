/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:45:42 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/14 16:53:15 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_world.h"
#include "ft_utils.h"
#include "ft_spheres.h"
#include "ft_camera.h"
#include "ft_parser.h"
#include "../.minilibx/mlx.h"
#include "ft_definitions.h"
#include "main.h"

int	ft_paint(t_canvas canvas)
{
	t_info	vars;

	vars.height = canvas.height;
	vars.width = canvas.width;
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, vars.width,
			vars.height, "MiniRt");
	vars.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel,
			&vars.line_length, &vars.endian);
	ft_draw(&vars, canvas);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img, 0, 0);
	mlx_hook(vars.mlx_win, 2, 1L << 0, close_win, &vars);
	mlx_hook(vars.mlx_win, 17, 0, close_win_2, &vars);
	mlx_loop(vars.mlx);
	ft_free_canvas(canvas);
	return (0);
}

void	ft_read_scene(int fd)
{
	char		*line;
	char		*word;
	t_world		world;
	t_canvas	canvas;

	world = ft_world();
	line = get_next_line(fd);
	while (line != NULL)
	{
		word = ft_get_word(line, 1);
		world = ft_parse_line(world, line, word);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fd = -1;
	while (++fd < world.n_spheres)
	{
		world.spheres[fd].material.ambient_color = world.ambient_color;
		world.spheres[fd].material.ambient = world.ambient_intensity;
	}
	if (world.ambient_def == 0 || world.camera_def == 0)
		ft_exit_error(0);
	canvas = ft_render(world.camera, world);
	ft_paint(canvas);
}

int	main(int argc, char *argv[])
{
	int	fd;

	if (argc == 2 && ft_is_rt(argv[1]))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > 0)
		{
			ft_read_scene(fd);
		}
		else
		{
			printf("ERROR\n");
			printf("File not found.\n");
		}
	}
	else
	{
		printf("ERROR\n");
		printf("Specify .rt file as input.\n");
	}
	return (0);
}
