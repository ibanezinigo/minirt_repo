/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_materials.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:02:50 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 19:44:08 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spheres.h"
#include "ft_materials.h"

t_material	ft_material(void)
{
	t_material	m;

	m.color = ft_color(1, 1, 1);
	m.ambient = 0.1;
	m.diffuse = 0.7;
	m.specular = 0.3;
	m.shininess = 200;
	m.has_pattern = 0;
	m.ambient_color = ft_color(255, 255, 255);
	return (m);
}

t_color	ft_get_effective_color(t_shape shape, t_material material,
			t_light light, t_tuple point)
{
	t_color	color;

	if (material.has_pattern)
		color = ft_pattern_at_shape(material.pattern, shape, point);
	else
		color = material.color;
	color = ft_color_add(ft_color_multiply_bycolor(color, light.intensity),
			ft_color_multiply_byscalar(material.ambient_color,
				material.ambient));
	return (color);
}

t_color	ft_get_specular(t_tuple lightv, t_comps c,
			t_material material, t_light light)
{
	t_color	specular;
	t_tuple	reflectv;
	float	reflect_dot_eye;
	float	factor;

	reflectv = ft_reflect(ft_multiply_tuple(lightv, -1), c.normalv);
	reflect_dot_eye = ft_tuple_dot(reflectv, c.eyev);
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
	return (specular);
}

t_color	ft_get_diffuse(t_color color, t_comps c, t_tuple lightv)
{
	t_color	diffuse;

	diffuse = ft_color_multiply_byscalar(
			ft_color_multiply_byscalar(color,
				c.object.material.diffuse),
			ft_tuple_dot(lightv, c.normalv));
	return (diffuse);
}

t_color	ft_lighting(t_shape shape, t_comps c, t_light light, int in_shadow)
{
	t_color	effective_color;
	t_tuple	lightv;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;

	effective_color = ft_get_effective_color(shape, c.object.material,
			light, c.over_point);
	lightv = ft_tuple_normalize(ft_subtract_tuples(light.position,
				c.over_point));
	ambient = ft_color_multiply_byscalar(effective_color,
			c.object.material.ambient);
	if (in_shadow == 1)
		return (ambient);
	if (ft_tuple_dot(lightv, c.normalv) < 0)
	{
		diffuse = ft_color(0, 0, 0);
		specular = ft_color(0, 0, 0);
	}
	else
	{
		diffuse = ft_get_diffuse(effective_color, c, lightv);
		specular = ft_get_specular(lightv, c, c.object.material, light);
	}
	return (ft_color_add(ft_color_add(ambient, diffuse), specular));
}
