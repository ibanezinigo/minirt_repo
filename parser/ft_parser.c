/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:18:23 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/14 13:34:35 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

t_world	ft_read_ambient_ligth(t_world w, char *line)
{
	char	*ambient;
	char	*color;

	ambient = ft_get_word(line, 2);
	w.ambient_intensity = ft_atof(ambient);
	free(ambient);
	if (w.ambient_intensity < 0 || w.ambient_intensity > 1)
		ft_exit_error(12);
	color = ft_get_word(line, 3);
	w.ambient_color = ft_read_color(color);
	w.ambient_def = 1;
	free(color);
	return (w);
}

t_world	ft_read_camera(t_world w, char *line)
{
	char		*str;
	t_camera	c;
	t_tuple		o;
	t_tuple		dir;

	str = ft_get_word(line, 4);
	c = ft_camera(216, 108, M_PI / 180.0 * ft_atof(str));
	if (ft_atof(str) < 0 || ft_atof(str) > 180)
		ft_exit_error(11);
	free(str);
	str = ft_get_word(line, 2);
	o = ft_read_coords(str);
	o = ft_create_point(o.x, o.y, o.z);
	free(str);
	str = ft_get_word(line, 3);
	dir = ft_read_coords(str);
	dir = ft_create_vector(dir.x, dir.y, dir.z);
	ft_validate_vector(dir);
	dir = ft_add_tuples(o, dir);
	free(str);
	c.transform = ft_view_transform(o, dir, ft_create_vector(0, 1, 0));
	w.camera = c;
	w.camera_def = 1;
	return (w);
}

t_world	ft_read_light(t_world w, char *line)
{
	char	*str;
	t_light	l;
	float	ratio;

	str = ft_get_word(line, 2);
	l.position = ft_read_coords(str);
	l.position.w = 1;
	free(str);
	str = ft_get_word(line, 4);
	l.intensity = ft_read_color(str);
	free(str);
	str = ft_get_word(line, 3);
	ratio = (float) ft_atof(str);
	if (ratio < 0 || ratio > 1)
		ft_exit_error(12);
	l.intensity = ft_color_multiply_byscalar(l.intensity, ratio);
	l = ft_point_light(l.position, l.intensity);
	free(str);
	return (ft_world_add_light(w, l));
}

t_tuple	ft_read_coords(char *str)
{
	t_tuple	c;
	int		i;

	i = 0;
	ft_notonlynums(str);
	ft_hassmthng(&str[i]);
	c.x = ft_atof(str);
	while (str[i] != '\0' && str[i] != ',')
		i++;
	ft_hassmthng(&str[i]);
	i++;
	c.y = ft_atof(&str[i]);
	while (str[i] != '\0' && str[i] != ',')
		i++;
	ft_hassmthng(&str[i]);
	i++;
	ft_endcorrect(&str[i]);
	c.z = ft_atof(&str[i]);
	c = ft_create_point(c.x, c.y, c.z);
	return (c);
}

t_color	ft_read_color(char *str)
{
	t_color	c;
	int		i;

	i = 0;
	ft_notonlynums(str);
	ft_hassmthng(&str[i]);
	c.red = ft_atof(str) / 255;
	while (str[i] != '\0' && str[i] != ',')
		i++;
	ft_hassmthng(&str[i]);
	i++;
	c.green = ft_atof(&str[i]) / 255;
	while (str[i] != '\0' && str[i] != ',')
		i++;
	ft_hassmthng(&str[i]);
	i++;
	ft_endcorrect(&str[i]);
	c.blue = ft_atof(&str[i]) / 255;
	c = ft_color(c.red, c.green, c.blue);
	ft_validate_color(c);
	return (c);
}
