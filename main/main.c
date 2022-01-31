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

int	ft_read_ambient_ligth(t_world *w, char *line)
{
	char	*ambient;
	char	*color;

	ambient = ft_get_word(line, 2);
	color = ft_get_word(line, 3);
	return (0);
}


int	ft_read_camera(t_world *w, char *line)
{
	char	*coords;
	char	*vector;
	char	*fov;

	coords = ft_get_word(line, 2);
	vector = ft_get_word(line, 3);
	fov = ft_get_word(line, 4);
	return (0);
}

int	ft_read_light(t_world *w, char *line)
{
	char	*coords;
	char	*ratio;
	char	*color;

	coords = ft_get_word(line, 2);
	ratio = ft_get_word(line, 3);
	color = ft_get_word(line, 4);

	free(coords);
	free(ratio);
	free(color);
	return (0);
}


t_tuple	ft_read_coords(char *str)
{
	char	*x;
	char	*y;
	char	*z;
	t_tuple	c;

	c = ft_create_point();
}

int	ft_read_sphere(t_world *w, char *line)
{
	char	*coords;
	char	*diam;
	char	*color;

	coords = ft_get_word(line, 2);
	diam = ft_get_word(line, 3);
	color = ft_get_word(line, 4);

	free(coords);
	free(diam);
	free(color);
	return (0);
}

int	ft_read_plane(t_world *w, char *line)
{
	char	*coords;
	char	*vector;
	char	*color;

	coords = ft_get_word(line, 2);
	vector = ft_get_word(line, 3);
	color = ft_get_word(line, 4);
	return (0);
}

int	ft_read_cylinder(t_world *w, char *line)
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
	return (0);
}

int	ft_parse_line(t_world *w, char *line)
{
	char	*word;

	word = ft_get_word(line, 1);
	if (ft_strequals(word, "A"))
		ft_read_ambient_ligth(w, line);
	else if (ft_strequals(word, "C"))
		ft_read_camera(w, line);
	else if (ft_strequals(word, "L"))
		ft_read_light(w, line);
	else if (ft_strequals(word, "sp"))
		ft_read_sphere(w, line);
	else if (ft_strequals(word, "pl"))
		ft_read_plane(w, line);
	else if (ft_strequals(word, "cy"))
		ft_read_cylinder(w, line);
	else
		printf("ERROR\n");
	free(word);
	return (0);
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
			ft_parse_line(&world, line);
			free(line);
		}
	}
	else
		printf("Specify .rt file as input.\n");
	return (0);
}