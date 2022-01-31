/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:45:42 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 20:36:39 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_world.h"
#include "ft_utils.h"
#include "ft_spheres.h"
#include "ft_camera.h"

t_color	ft_read_color(char *str);
t_tuple	ft_read_coords(char *str);

int	ft_is_rt(char *str)
{
	int	len;
	
	len = ft_strlen(str, 0);
	if (len > 3 && str[len - 3] == '.' &&str[len - 2] == 'r' && str[len - 1] == 't')
		return (1);
	return (0);
}

int	ft_strisspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_strequals(char *s1, char *s2)
{
	int	i;

	if (ft_strlen(s1, '\0') != ft_strlen(s2, '\0'))
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_get_word(char *str, int nword)
{
	int		init;
	int		nw;
	int		len;
	char	*word;
	int		i;

	nw = 0;
	init = 0;
	while (nw < nword)
	{
		while (str[init] != '\0' && ft_strisspace(str[init]) == 1)
			init++;
		nw++;
		if (nw < nword)
		{
			while (str[init] != '\0' && ft_strisspace(str[init]) == 0)
				init++;
		}
	}
	len = 0;
	while (str[init + len] != '\0' && ft_strisspace(str[init + len]) == 0)
		len++;
	word = malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		word[i] = str[init + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

t_world	ft_read_ambient_ligth(t_world w, char *line)
{
	char	*ambient;
	char	*color;

	ambient = ft_get_word(line, 2);
	color = ft_get_word(line, 3);
	return (w);
}

t_world	ft_read_camera(t_world w, char *line)
{
	char		*str;
	t_camera	c;
	t_tuple		o;
	t_tuple		dir;

	str = ft_get_word(line, 4);
	c = ft_camera(1920, 1080, M_PI / 180 * ft_atof(str));
	free(str);

	str = ft_get_word(line, 2);
	o = ft_read_coords(str);
	free(str);
	
	str = ft_get_word(line, 3);
	dir = ft_read_coords(str);
	free(str);

	c.transform = ft_matrix_scaling(dir.x, dir.y, dir.z);
	c.transform = ft_matrix_multiply(c.transform, ft_matrix_translation(o.x, o.y, o.z));

	w.camera = c;
	return (w);
}

t_world	ft_read_light(t_world w, char *line)
{
	char	*str;
	t_light	l;
	float	ratio;

	str = ft_get_word(line, 2);
	l.position = ft_read_coords(str);
	free(str);
	str = ft_get_word(line, 3);
	l.intensity = ft_read_color(str);
	free(str);
	str = ft_get_word(line, 4);
	ratio = (float) ft_atof(str);
	l.intensity = ft_color_multiply_byscalar(l.intensity, ratio);
	free(str);
	return (ft_world_add_light(w, l));
}

t_tuple	ft_read_coords(char *str)
{
	t_tuple	c;
	int		i;

	c.x = ft_atof(str);
	i = 0;
	while (str[i] != '\0' && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	c.y = ft_atof(&str[i]);
	while (str[i] != '\0' && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	c.z = ft_atof(&str[i]);
	c = ft_create_point(c.x, c.y, c.z);
	return (c);
}

t_color	ft_read_color(char *str)
{
	t_color	c;
	int		i;

	c.red = ft_atof(str);
	i = 0;
	while (str[i] != '\0' && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	c.green = ft_atof(&str[i]);
	while (str[i] != '\0' && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	c.blue = ft_atof(&str[i]);
	c = ft_color(c.red, c.green, c.blue);
	return (c);
}

t_world	ft_read_sphere(t_world w, char *line)
{
	char	*str;
	t_tuple	o;
	t_shape	s;
	float	fdiam;
	t_color	color;

	s = ft_create_sphere();
	str = ft_get_word(line, 3);
	fdiam = (float) ft_atof(str);
	free(str);
	str = ft_get_word(line, 2);
	o = ft_read_coords(str);
	s.transform = ft_matrix_multiply(
					ft_matrix_scaling(fdiam, fdiam, fdiam),
					ft_matrix_translation(o.x, o.y, o.z));
	free(str);
	str = ft_get_word(line, 4);
	color = ft_read_color(str);
	free(str);
	s.material = ft_material();
	s.material.color = color;
	return (ft_world_add_sphere(w, s));
}

t_world	ft_read_plane(t_world w, char *line)
{
	char	*str;
	char	*vector;
	char	*color;
	t_shape	p;
	t_tuple	dir;
	t_tuple	o;

	p = ft_plane();
	str = ft_get_word(line, 2);
	o = ft_read_coords(str);
	free(str);

	str = ft_get_word(line, 3);
	dir = ft_tuple_normalize(ft_read_coords(str));
	p.transform = ft_matrix_multiply(
					ft_matrix_scaling(dir.x, dir.y, dir.z),
					ft_matrix_translation(o.x, o.y, o.z));
	free(str);

	str = ft_get_word(line, 4);
	p.material.color = ft_read_color(str);
	free(str);

	return (ft_world_add_sphere(w, p));
}

t_world	ft_read_cylinder(t_world w, char *line)
{
	char	*coords;
	char	*vector;
	char	*diam;
	char	*height;
	char	*color;

	coords = ft_get_word(line, 2);
	vector = ft_get_word(line, 3);
	diam = ft_get_word(line, 4);
	height = ft_get_word(line, 5);
	color = ft_get_word(line, 6);

	free(coords);
	free(vector);
	free(diam);
	free(height);
	free(color);
	return (w);
}

t_world	ft_parse_line(t_world w, char *line)
{
	char	*word;

	word = ft_get_word(line, 1);
	if (ft_strequals(word, "A"))
		w = ft_read_ambient_ligth(w, line);
	else if (ft_strequals(word, "C"))
		w = ft_read_camera(w, line);
	else if (ft_strequals(word, "L"))
		w = ft_read_light(w, line);
	else if (ft_strequals(word, "sp"))
		w = ft_read_sphere(w, line);
	else if (ft_strequals(word, "pl"))
		w = ft_read_plane(w, line);
	else if (ft_strequals(word, "cy"))
		w = ft_read_cylinder(w, line);
	else
	{
		printf("ERROR\n");
		free(word);
		exit(0);
	}
	free(word);
	return (w);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	t_world	world;

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
		ft_render(world.camera, world);
	}
	else
		printf("Specify .rt file as input.\n");
	return (0);
}