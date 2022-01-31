/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_definitions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:54:51 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 11:51:10 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFINITIONS_H
# define FT_DEFINITIONS_H

# include <stdlib.h>

typedef struct s_matrix
{
	size_t	rows;
	size_t	cols;
	float	data[4][4];
}	t_matrix;

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

typedef struct s_color
{
	float	red;
	float	green;
	float	blue;
}	t_color;

typedef struct s_pattern
{
	t_color		a;
	t_color		b;
	t_matrix	transform;
	int			pattern_type;
}	t_pattern;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct s_material
{
	t_color		color;
	float		ambient;
	float		diffuse;
	float		specular;
	float		shininess;
	int			has_pattern;
	t_pattern	pattern;
}	t_material;

typedef struct s_shape
{
	t_matrix	transform;
	t_material	material;
	t_ray		saved_ray;
	int			shape_type;
	float		minimum;
	float		maximum;
	int			closed;
}	t_shape;

typedef struct s_intersection
{
	float		t;
	t_shape		object;
}	t_intersection;

typedef struct s_intersections
{
	int				count;
	t_intersection	*xs;
}	t_intersections;

typedef struct s_light
{
	t_tuple	position;
	t_color	intensity;
}	t_light;

typedef struct s_camera
{
	size_t		hsize;
	size_t		vsize;
	float		field_of_view;
	t_matrix	transform;
	float		pixel_size;
	float		half_width;
	float		half_height;
}	t_camera;

typedef struct s_canvas
{
	size_t	width;
	size_t	height;
	t_color	**pixel;
}	t_canvas;

typedef struct s_world
{
	int			n_lights;
	t_light		*lights;
	int			n_spheres;
	t_shape		*spheres;
	t_camera	camera;

}	t_world;

typedef struct s_comps
{
	float		t;
	t_shape		object;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
	int			inside;
	t_tuple		over_point;
}	t_comps;
#endif