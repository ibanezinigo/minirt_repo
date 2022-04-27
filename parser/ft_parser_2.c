/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:19:14 by iibanez-          #+#    #+#             */
/*   Updated: 2022/04/27 17:49:20 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "ft_tuples.h"
#include "ft_definitions.h"

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
			ft_matrix_scaling(fdiam / 2, fdiam / 2, fdiam / 2)
			);
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
	ft_validate_vector(dir);
	dir = ft_tuple_normalize(dir);
	p.transform = ft_identity_matrix();
	
	p.transform = ft_matrix_multiply(p.transform,
			ft_matrix_rotation_x(dir.z * (M_PI / 2)));
	p.transform = ft_matrix_multiply(p.transform,
			ft_matrix_rotation_z(dir.x * (M_PI / 2)));
	p.transform = ft_matrix_multiply(p.transform,
			ft_matrix_translation(o.x, o.y, o.z));
	free(str);
	str = ft_get_word(line, 4);
	p.material.color = ft_read_color(str);
	free(str);
	return (ft_world_add_sphere(w, p));
}

t_shape	ft_read_cylinder_2(t_shape cyl, char *line, float num)
{
	char	*str;
	t_tuple	o;	

	str = ft_get_word(line, 2);
	o = ft_read_coords(str);
	free(str);
	cyl.transform = ft_matrix_multiply(cyl.transform,
			ft_matrix_translation(o.x, o.y, o.z));
	str = ft_get_word(line, 3);
	o = ft_read_coords(str);
	ft_validate_vector(o);
	free(str);
	cyl.transform = ft_matrix_multiply(cyl.transform,
			ft_matrix_rotation_x(o.z * (M_PI / 2)));
	cyl.transform = ft_matrix_multiply(cyl.transform,
			ft_matrix_rotation_z(o.x * (M_PI / 2)));
	cyl.transform = ft_matrix_multiply(cyl.transform,
			ft_matrix_scaling(num / 2, num / 2, num / 2));
	cyl.maximum = cyl.maximum / num;
	return (cyl);
}

t_world	ft_read_cylinder(t_world w, char *line)
{
	char	*str;
	t_shape	cyl;
	t_color	color;
	float	num;

	str = ft_get_word(line, 6);
	color = ft_read_color(str);
	free(str);
	cyl = ft_cylinder();
	cyl.material.color = color;
	str = ft_get_word(line, 5);
	num = ft_atof(str);
	free(str);
	cyl.maximum = num * 2;
	str = ft_get_word(line, 4);
	num = ft_atof(str);
	free(str);
	cyl = ft_read_cylinder_2(cyl, line, num);
	return (ft_world_add_sphere(w, cyl));
}

void	ft_exit_parser(char *word)
{
	printf("ERROR\nmalformed .rt file\n");
	free(word);
	exit(0);
}
