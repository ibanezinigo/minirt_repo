/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:19:14 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 16:32:36 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

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
			ft_matrix_translation(o.x, o.y, o.z),
			ft_matrix_scaling(fdiam, fdiam, fdiam));
	free(str);
	str = ft_get_word(line, 4);
	color = ft_read_color(str);
	free(str);
	s.material = ft_material();
	s.material.color = color;
	s.material.ambient_color = w.ambient_color;
	s.material.ambient = w.ambient_intensity;
	return (ft_world_add_sphere(w, s));
}

t_world	ft_read_plane(t_world w, char *line)
{
	char	*str;
	t_shape	p;
	t_tuple	dir;
	t_tuple	o;

	p = ft_plane();
	str = ft_get_word(line, 2);
	o = ft_read_coords(str);
	free(str);
	str = ft_get_word(line, 3);
	dir = ft_read_coords(str);
	dir.w = 0;
	dir = ft_tuple_normalize(dir);
	p.transform = ft_identity_matrix();
	p.transform = ft_matrix_multiply(p.transform,
			ft_matrix_translation(o.x, o.y, o.z));
	p.transform = ft_matrix_multiply(p.transform,
			ft_matrix_rotation_x(dir.z * (M_PI / 2)));
	p.transform = ft_matrix_multiply(p.transform,
			ft_matrix_rotation_z(dir.x * (M_PI / 2)));
	p.material.ambient_color = w.ambient_color;
	p.material.ambient = w.ambient_intensity;
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
