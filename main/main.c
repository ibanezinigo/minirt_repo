/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:45:42 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 16:24:45 by iibanez-         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	t_world	world;

	world = ft_world();
	if (argc == 2 && ft_is_rt(argv[1]))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > 0)
		{
			line = get_next_line(fd);
			while (line != NULL)
			{
				world = ft_parse_line(world, line);
				free(line);
				line = get_next_line(fd);
			}
		}
		ft_canvas_to_ppm(ft_render(world.camera, world));
	}
	else
		printf("Specify .rt file as input.\n");
	return (0);
}
