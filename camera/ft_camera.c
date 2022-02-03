/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:03:27 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 16:51:08 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_camera.h"

t_camera	ft_camera(int h, int v, float field)
{
	t_camera	cam;
	float		aspect;
	float		half_view;

	cam.hsize = h;
	cam.vsize = v;
	cam.field_of_view = field;
	cam.transform = ft_identity_matrix();
	half_view = tanf(cam.field_of_view / 2);
	aspect = cam.hsize / cam.vsize;
	if (aspect >= 1)
	{
		cam.half_width = half_view;
		cam.half_height = half_view / aspect;
	}
	else
	{
		cam.half_width = half_view * aspect;
		cam.half_height = half_view;
	}
	cam.pixel_size = (cam.half_width * 2) / cam.hsize;
	return (cam);
}

t_ray	ft_ray_for_pixel(t_camera cam, float px, float py)
{
	float	world_x;
	float	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	world_x = cam.half_width - ((px + 0.5) * cam.pixel_size);
	world_y = cam.half_height - ((py + 0.5) * cam.pixel_size);
	pixel = ft_multiply_matrix_tuple(ft_inverse(cam.transform),
			ft_create_point(world_x, world_y, -1));
	origin = ft_multiply_matrix_tuple(ft_inverse(cam.transform),
			ft_create_point(0, 0, 0));
	direction = ft_tuple_normalize(ft_subtract_tuples(pixel, origin));
	return (ft_ray(origin, direction));
}

t_canvas	ft_render(t_camera camera, t_world world)
{
	t_canvas	image;
	t_ray		ray;
	t_color		color;
	size_t		x;
	size_t		y;

	image = ft_canvas(camera.hsize, camera.vsize);
	printf("v->%zu h->%zu\n", camera.vsize, camera.hsize);
	y = 0;
	while (y < camera.vsize)
	{
		x = 0;
		while (x < camera.hsize)
		{
			ray = ft_ray_for_pixel(camera, x, y);
			color = ft_color_at(world, ray);
			ft_write_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
	return (image);
}
