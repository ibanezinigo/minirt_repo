/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_materials.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:02:50 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/27 19:17:01 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spheres.h"
#include "ft_materials.h"

t_material	ft_material(void)
{
	t_material	m;

	m.color = ft_color(1, 1, 1);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	m.has_pattern = 0;
	return (m);
}

t_color	ft_lighting(t_material material, t_light light, t_tuple point,
	t_tuple eyev, t_tuple normalv, int in_shadow)
{
	t_color	effective_color;
	t_tuple	lightv;
	t_color	ambient;
	float	light_dot_normal;
	t_color	diffuse;
	t_color	specular;
	t_tuple	reflectv;
	float	reflect_dot_eye;
	float	factor;
	t_color	color;

	if (material.has_pattern)
		color = ft_stripe_at(material.pattern, point);
	else
		color = material.color;
	effective_color = ft_color_multiply_bycolor(color, light.intensity);
	lightv = ft_tuple_normalize(ft_subtract_tuples(light.position, point));
	ambient = ft_color_multiply_byscalar(effective_color, material.ambient);
	light_dot_normal = ft_tuple_dot(lightv, normalv);
	if (in_shadow == 1)
		return (ambient);
	if (light_dot_normal < 0)
	{
		diffuse = ft_color(0, 0, 0);
		specular = ft_color(0, 0, 0);
	}
	else
	{
		diffuse = ft_color_multiply_byscalar(
				ft_color_multiply_byscalar(effective_color, material.diffuse),
				light_dot_normal);
		reflectv = ft_reflect(ft_multiply_tuple(lightv, -1), normalv);
		reflect_dot_eye = ft_tuple_dot(reflectv, eyev);
		if (reflect_dot_eye <= 0)
		{
			specular = ft_color(0, 0, 0);
		}
		else
		{
			factor = powf(reflect_dot_eye, material.shininess);
			specular = ft_color_multiply_byscalar(
					ft_color_multiply_byscalar(
						light.intensity, material.specular), factor);
		}
	}
	return (ft_color_add(ft_color_add(ambient, diffuse), specular));
}
