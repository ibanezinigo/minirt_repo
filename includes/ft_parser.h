/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:19:58 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 16:26:19 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_world.h"
# include "ft_utils.h"
# include "ft_camera.h"

t_world	ft_read_ambient_ligth(t_world w, char *line);
t_world	ft_read_camera(t_world w, char *line);
t_world	ft_read_light(t_world w, char *line);
t_tuple	ft_read_coords(char *str);
t_color	ft_read_color(char *str);
t_world	ft_read_sphere(t_world w, char *line);
t_world	ft_read_plane(t_world w, char *line);
t_world	ft_read_cylinder(t_world w, char *line);
t_world	ft_parse_line(t_world w, char *line);

#endif