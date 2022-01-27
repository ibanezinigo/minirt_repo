#include "ft_camera.h"

t_camera ft_camera(int  h, int v, float field)
{
	t_camera    cam;
	float       aspect;
	float       half_view;

	cam.hsize = h;
	cam.vsize = v;
	cam.field_of_view = field;
	cam.transform = ft_matrix(4,4);
	cam.transform.data[0][0] = 1;
	cam.transform.data[1][1] = 1;
	cam.transform.data[2][2] = 1;
	cam.transform.data[3][3] = 1;
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
	t_ray	ray;
	float	xoffset;
	float	yoffset;
	float	world_x;
	float	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	xoffset = (px + 0.5) * cam.pixel_size;
	yoffset = (py + 0.5) * cam.pixel_size;
	world_x = cam.half_width - xoffset;
	world_y = cam.half_height - yoffset;
	pixel = ft_multiply_matrix_tuple(ft_inverse(cam.transform), ft_create_point(world_x, world_y, -1));
	origin = ft_multiply_matrix_tuple(ft_inverse(cam.transform), ft_create_point(0, 0, 0));
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
			//printf("y-> %zu x-> %zu %f %f %f\n", y, x, color.red, color.green, color.blue);
			ft_write_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
	return (image);
}