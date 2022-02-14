/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:18:34 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/14 17:13:53 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

t_world	ft_parse_line(t_world w, char *line, char *word)
{
	if (word && word[0] != '\0')
	{
		if (ft_strequals(word, "A") && w.ambient_def == 0)
			w = ft_read_ambient_ligth(w, line);
		else if (ft_strequals(word, "C") && w.camera_def == 0)
			w = ft_read_camera(w, line);
		else if (ft_strequals(word, "L"))
			w = ft_read_light(w, line);
		else if (ft_strequals(word, "sp"))
			w = ft_read_sphere(w, line);
		else if (ft_strequals(word, "pl"))
			w = ft_read_plane(w, line);
		else if (ft_strequals(word, "PL"))
			w = ft_read_plane_2(w, line);
		else if (ft_strequals(word, "cy"))
			w = ft_read_cylinder(w, line);
		else if (ft_strequals(word, "co"))
			w = ft_read_cone(w, line);
		else
			ft_exit_parser(word);
	}
	free(word);
	return (w);
}

t_world	ft_read_cone(t_world w, char *line)
{
	char	*str;
	t_shape	cone;
	t_color	color;
	float	num;
	t_tuple	o;	

	str = ft_get_word(line, 4);
	color = ft_read_color(str);
	free(str);
	cone = ft_cone();
	cone.material.color = color;
	str = ft_get_word(line, 3);
	num = ft_atof(str);
	free(str);
	cone.closed = 1;
	cone.minimum = num * -1;
	cone.maximum = 0;
	cone.transform = ft_identity_matrix();
	str = ft_get_word(line, 2);
	o = ft_read_coords(str);
	free(str);
	cone.transform = ft_matrix_multiply(cone.transform,
			ft_matrix_translation(o.x, o.y, o.z));
	return (ft_world_add_sphere(w, cone));
}

void	ft_endcorrect(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			ft_exit_error(10);
		i++;
	}
}

t_world	ft_read_plane_2(t_world w, char *line)
{
	t_world	nw;

	nw = ft_read_plane(w, line);
	nw.spheres[w.n_spheres].material.has_pattern = 1;
	nw.spheres[w.n_spheres].material.pattern = ft_checker_pattern(
			ft_color(0, 0, 0), ft_color(1, 1, 1));
	return (nw);
}
