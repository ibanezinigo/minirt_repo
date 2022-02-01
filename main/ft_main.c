/*#include <math.h>
#include <stdlib.h>*/
#include <stdio.h>
#include "ft_canvas.h"
#include "ft_intersections.h"
#include "ft_lights.h"
#include "ft_materials.h"
#include "ft_matrices.h"
#include "ft_rays.h"
#include "ft_spheres.h"
#include "ft_transformations.h"
#include "ft_tuples.h"
#include "ft_world.h"
#include "ft_camera.h"
#include "ft_patterns.h"
#include "ft_shapes.h"
#include "ft_planes.h"
#include "ft_cylinders.h"
#include "ft_cones.h"
#include "main.h"


int	main(void)
{
	t_canvas	canvas;
	t_world		world;
	t_camera	camera;
	t_shape		middle;
	t_shape		right;
	t_shape		left;
	t_light		light;
	t_shape		plane;
	t_shape		plane2;
	t_shape		cyl;
	t_shape		cone;

	plane = ft_plane();
	plane.transform = ft_matrix_multiply(ft_matrix_translation(0, 0, 40),ft_matrix_rotation_x(M_PI / 2));
	plane.material = ft_material();
	plane.material.color = ft_color(0.5, 1, 0.1);
	//plane.material.pattern = ft_checker_pattern(ft_color(1,1,1), ft_color(0,0,0));
	//plane.material.has_pattern = 1;
	//plane.material.pattern.transform = ft_matrix_multiply(ft_matrix_scaling(0.2, 0.1, 0.2), ft_matrix_rotation_z(M_PI/3));

	plane2 = ft_plane();
	plane2.transform = ft_matrix_multiply(ft_matrix_translation(0, 0, 50), ft_matrix_rotation_y(M_PI / 4));
	plane2.material = ft_material();
	plane2.material.color = ft_color(0.5, 0.5, 0.5);
	//plane2.material.pattern = ft_checker_pattern(ft_color(1,1,1), ft_color(0,0,0));
	//plane2.material.has_pattern = 1;
	//plane2.material.pattern.transform = ft_matrix_rotation_z(M_PI/3);*/

	middle = ft_create_sphere();
	middle.transform = ft_matrix_translation(-0.5, 1, 0.5);
	middle.material = ft_material();
	middle.material.color = ft_color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	//middle.material.pattern = ft_gradient_pattern(ft_color(1, 1, 1), ft_color(0, 0, 0));
	//middle.material.pattern.transform = ft_matrix_scaling(0.5, 0.5, 0.5);
	//middle.material.has_pattern = 1;
	printf("middle\n");

	/*right = ft_create_sphere();
	right.transform = ft_matrix_multiply(ft_matrix_translation(1.5, 0.5, -0.5), ft_matrix_scaling(0.5, 0.5, 0.5));
	right.material = ft_material();
	right.material.color = ft_color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;
	printf("right\n");

	left = ft_create_sphere();
	left.transform = ft_matrix_multiply(ft_matrix_translation(-1.5, 0.33, -0.75), ft_matrix_scaling(0.33, 0.33, 0.33));
	left.material = ft_material();
	left.material.color = ft_color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;
	printf("left\n");

	cyl = ft_cylinder();
	cyl.transform = ft_matrix_multiply(ft_matrix_multiply(ft_matrix_translation(0.5, 0, -0.5), ft_matrix_scaling(0.5, 0.5, 0.5)), ft_matrix_rotation_x(M_PI / 4 * -1));
	cyl.material.color = ft_color(0, 1, 0);
	cyl.material.diffuse = 0.7;
	cyl.material.specular = 0.3;
	cyl.closed = 1;
	cyl.minimum = 1;
	cyl.maximum = 3;

	cone = ft_cone();
	cone.material.color = ft_color(0.25, 0.25, 0.25);
	cone.material.diffuse = 0.7;
	cone.material.specular = 0.3;
	cone.minimum = -1;
	cone.maximum = 0;
	cone.closed = 1;
	cone.transform = ft_matrix_translation(-2, 1, 1);*/

	light = ft_point_light(ft_create_point(-10, 10, -10), ft_color(1, 1, 1));
	world = ft_world();
	world = ft_world_add_light(world, light);
	world = ft_world_add_sphere(world, middle);
	/*world = ft_world_add_sphere(world, right);
	world = ft_world_add_sphere(world, left);*/
	world = ft_world_add_sphere(world, plane);
	world = ft_world_add_sphere(world, plane2);
	/*world = ft_world_add_sphere(world, cyl);
	world = ft_world_add_sphere(world, cone);*/

	printf("world\n");
	printf("%i %i\n", world.n_lights, world.n_spheres);
	printf("%f %f %f %f\n", world.lights[0].position.x, world.lights[0].position.y, world.lights[0].position.z, world.lights[0].position.w);
	printf("%f %f %f\n", world.lights[0].intensity.red, world.lights[0].intensity.green, world.lights[0].intensity.blue);

	camera = ft_camera(500, 250, M_PI/3);
	camera.transform = ft_view_transform(ft_create_point(0, 1.5, -5), ft_create_point(0, 1, 0), ft_create_vector(0, 1, 0));
	printf("camera\n");
	ft_print_matrix(camera.transform);

	ft_print_world(world);
	canvas = ft_render(camera, world);
	printf("render\n");
	ft_canvas_to_ppm(canvas);
	printf("ppm\n");

	ft_free_canvas(canvas);
	free(world.spheres);
	free(world.lights);
	
	return (0);
}

/*
int	main(void)
{
	t_pattern pattern = ft_checker_pattern(ft_color(1, 1, 1), ft_color(0, 0, 0));
	t_color c = ft_pattern_at_checker(pattern, ft_create_point(0,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(0.99,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(1.01,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	printf("\n");

	c = ft_pattern_at_checker(pattern, ft_create_point(0,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(0, 0.99,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(0, 1.01,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	printf("\n");

	c = ft_pattern_at_checker(pattern, ft_create_point(0,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(0,0, 0.99));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(0,0, 1.01));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	return (0);
}*/

/*
int	main(void)
{
	t_shape shape = ft_cone();
	t_tuple n = ft_normal_at_cone(shape, ft_create_point(0,0,0));
	printf("%f %f %f\n", n.x, n.y, n.z);

	n = ft_normal_at_cone(shape, ft_create_point(1,1,1));
	printf("%f %f %f\n", n.x, n.y, n.z);

	n = ft_normal_at_cone(shape, ft_create_point(-1,-1,0));
	printf("%f %f %f\n", n.x, n.y, n.z);

	return (0);
}
*/

/*
int	main(void)
{
	t_shape shape = ft_cone();
	shape.minimum = -0.5;
	shape.maximum = 0.5;
	shape.closed = 1;
	t_tuple direction = ft_tuple_normalize(ft_create_vector(0, 1, 0));
	t_ray r = ft_ray(ft_create_point(0, 0, -5), direction);
	t_intersections xs = ft_cones_intersect(shape, r);
	printf("%i\n", xs.count);

	direction = ft_tuple_normalize(ft_create_vector(0, 1, 1));
	r = ft_ray(ft_create_point(0, 0, -0.25), direction);
	xs = ft_cones_intersect(shape, r);
	printf("%i\n", xs.count);
	printf("%f\n", xs.xs[0].t);
	printf("%f\n", xs.xs[1].t);

	direction = ft_tuple_normalize(ft_create_vector(0, 1, 0));
	r = ft_ray(ft_create_point(0, 0, -0.25), direction);
	xs = ft_cones_intersect(shape, r);
	printf("%i\n", xs.count);
	printf("%f\n", xs.xs[0].t);
	printf("%f\n", xs.xs[1].t);
	return (0);
}*/

/*
int	main(void)
{
	t_shape shape = ft_cone();
	t_tuple direction = ft_tuple_normalize(ft_create_vector(0, 1, 1));
	t_ray r = ft_ray(ft_create_point(0, 0, -1), direction);
	t_intersections xs = ft_cones_intersect(shape, r);
	printf("%i\n", xs.count);
	printf("%f\n", xs.xs[0].t);
	return (0);
}*/

/*
int	main(void)
{
	t_shape shape = ft_cone();
	t_tuple	direction = ft_tuple_normalize(ft_create_vector(0, 0, 1));
	t_ray r = ft_ray(ft_create_point(0, 0, -5), direction);
	t_intersections xs = ft_cones_intersect(shape, r);
	printf("%i\n", xs.count);
	printf("%f\n", xs.xs[0].t);
	printf("%f\n\n", xs.xs[1].t);

	shape = ft_cone();
	direction = ft_tuple_normalize(ft_create_vector(1, 1, 1));
	r = ft_ray(ft_create_point(0, 0, -5), direction);
	xs = ft_cones_intersect(shape, r);
	printf("%i\n", xs.count);
	printf("%f\n", xs.xs[0].t);
	printf("%f\n\n", xs.xs[1].t);

	shape = ft_cone();
	direction = ft_tuple_normalize(ft_create_vector(-0.5, -1, 1));
	r = ft_ray(ft_create_point(1, 1, -5), direction);
	xs = ft_cones_intersect(shape, r);
	printf("%i\n", xs.count);
	printf("%f\n", xs.xs[0].t);
	printf("%f\n\n", xs.xs[1].t);

	return (0);
}*/

/*
int	main(void)
{
	t_canvas	canvas;
	t_world		world;
	t_camera	camera;
	t_shape		middle;
	t_shape		right;
	t_shape		left;
	t_light		light;
	t_shape		plane;
	t_shape		plane2;
	t_shape		cyl;

	plane = ft_plane();
	plane.transform = ft_matrix_multiply(ft_matrix_rotation_x(M_PI / 2), ft_matrix_translation(0, 0, 40));
	plane.material.color = ft_color(0.5, 1, 0.1);
	plane.material.diffuse = 0.7;
	plane.material.specular = 0.3;
	plane.material.pattern = ft_checker_pattern(ft_color(1,1,1), ft_color(0,0,0));
	plane.material.has_pattern = 1;
	//plane.material.pattern.transform = ft_matrix_multiply(ft_matrix_scaling(0.2, 0.1, 0.2), ft_matrix_rotation_z(M_PI/3));



	plane2 = ft_plane();
	plane2.transform = ft_matrix_multiply(ft_matrix_rotation_y(M_PI / 4), ft_matrix_translation(0, 0, 50));
	plane2.material.color = ft_color(0.2, 1, 0.1);
	plane2.material.diffuse = 0.7;
	plane2.material.specular = 0.3;
	//plane2.material.pattern = ft_checker_pattern(ft_color(1,1,1), ft_color(0,0,0));
	//plane2.material.has_pattern = 1;
	//plane2.material.pattern.transform = ft_matrix_rotation_z(M_PI/3);

	middle = ft_create_sphere();
	middle.transform = ft_matrix_translation(-0.5, 1, 0.5);
	middle.material = ft_material();
	middle.material.color = ft_color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	middle.material.pattern = ft_gradient_pattern(ft_color(1, 1, 1), ft_color(0, 0, 0));
	//middle.material.pattern.transform = ft_matrix_scaling(0.5, 0.5, 0.5);
	middle.material.has_pattern = 1;
	printf("middle\n");

	right = ft_create_sphere();
	right.transform = ft_matrix_multiply(ft_matrix_translation(1.5, 0.5, -0.5), ft_matrix_scaling(0.5, 0.5, 0.5));
	right.material = ft_material();
	right.material.color = ft_color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;
	printf("right\n");

	left = ft_create_sphere();
	left.transform = ft_matrix_multiply(ft_matrix_translation(-1.5, 0.33, -0.75), ft_matrix_scaling(0.33, 0.33, 0.33));
	left.material = ft_material();
	left.material.color = ft_color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;
	printf("left\n");

	cyl = ft_cylinder();
	cyl.transform = ft_matrix_multiply(ft_matrix_multiply(ft_matrix_translation(0.5, 0, -0.5), ft_matrix_scaling(0.5, 0.5, 0.5)), ft_matrix_rotation_x(M_PI / 4 * -1));
	cyl.material.color = ft_color(0, 1, 0);
	cyl.material.diffuse = 0.7;
	cyl.material.specular = 0.3;
	cyl.closed = 1;
	cyl.minimum = 1;
	cyl.maximum = 3;

	light = ft_point_light(ft_create_point(-10, 10, -10), ft_color(1, 1, 1));
	world = ft_world();
	world = ft_world_add_light(world, light);
	world = ft_world_add_sphere(world, middle);
	world = ft_world_add_sphere(world, right);
	world = ft_world_add_sphere(world, left);
	world = ft_world_add_sphere(world, plane);
	world = ft_world_add_sphere(world, plane2);
	world = ft_world_add_sphere(world, cyl);

	printf("world\n");
	printf("%i %i\n", world.n_lights, world.n_spheres);
	printf("%f %f %f %f\n", world.lights[0].position.x, world.lights[0].position.y, world.lights[0].position.z, world.lights[0].position.w);
	printf("%f %f %f\n", world.lights[0].intensity.red, world.lights[0].intensity.green, world.lights[0].intensity.blue);

	camera = ft_camera(500, 250, M_PI/3);
	camera.transform = ft_view_transform(ft_create_point(0, 1.5, -5), ft_create_point(0, 1, 0), ft_create_vector(0, 1, 0));
	printf("camera\n");
	ft_print_matrix(camera.transform);

	canvas = ft_render(camera, world);
	printf("render\n");
	ft_canvas_to_ppm(canvas);
	printf("ppm\n");

	ft_free_canvas(canvas);
	free(world.spheres);
	free(world.lights);
	
	return (0);
}*/

/*
int	main(void)
{
	t_pattern pattern = ft_checker_pattern(ft_color(1, 1, 1), ft_color(0, 0, 0));
	t_color c = ft_pattern_at_checker(pattern, ft_create_point(0,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(0.99,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(1.01,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	printf("\n");

	c = ft_pattern_at_checker(pattern, ft_create_point(0,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(0, 0.99,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(0, 1.01,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	printf("\n");

	c = ft_pattern_at_checker(pattern, ft_create_point(0,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(0,0, 0.99));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_checker(pattern, ft_create_point(0,0, 1.01));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	return (0);
}*/

/*
int	main(void)
{
	t_pattern pattern = ft_ring_pattern(ft_color(1, 1, 1), ft_color(0, 0, 0));
	t_color c = ft_pattern_at_ring(pattern, ft_create_point(0,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_ring(pattern, ft_create_point(1,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_ring(pattern, ft_create_point(0,0,1));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_ring(pattern, ft_create_point(0.708,0,0.708));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	return (0);
}*/

/*
int	main(void)
{
	t_pattern pattern = ft_gradient_pattern(ft_color(1, 1, 1), ft_color(0, 0, 0));
	t_color c = ft_pattern_at_gradient(pattern, ft_create_point(0, 0, 0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_gradient(pattern, ft_create_point(0.25, 0, 0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_gradient(pattern, ft_create_point(0.5, 0, 0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_pattern_at_gradient(pattern, ft_create_point(0.75, 0, 0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
}*/

/*
int	main(void)
{
	t_shape object = ft_create_sphere();
	ft_set_transform(&object, ft_matrix_scaling(2, 2, 2));
	t_pattern pattern = ft_stripe_pattern(ft_color(1, 1, 1), ft_color(0,0,0));
	t_color c = ft_pattern_at_shape(pattern, object, ft_create_point(2, 3, 4));
	printf("%f %f %f\n", c.red, c.green, c.blue);

	object = ft_create_sphere();
	pattern = ft_stripe_pattern(ft_color(1, 1, 1), ft_color(0,0,0));
	pattern.transform = ft_matrix_scaling(2, 2, 2);
	c = ft_pattern_at_shape(pattern, object, ft_create_point(2, 3, 4));
	printf("%f %f %f\n", c.red, c.green, c.blue);

	object = ft_create_sphere();
	ft_set_transform(&object, ft_matrix_scaling(2, 2, 2));
	pattern = ft_stripe_pattern(ft_color(1, 1, 1), ft_color(0,0,0));
	pattern.transform = ft_matrix_translation(0.5, 1, 1.5);
	c = ft_pattern_at_shape(pattern, object, ft_create_point(2.5, 3, 3.5));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	return (0);
}*/

/*
int	main(void)
{
	t_canvas	canvas;
	t_world		world;
	t_camera	camera;
	t_shape		middle;
	t_shape		right;
	t_shape		left;
	t_light		light;
	t_shape		plane;
	t_shape		plane2;
	t_shape		cyl;

	plane = ft_plane();
	plane.transform = ft_matrix_multiply(ft_matrix_rotation_x(M_PI / 2), ft_matrix_translation(0, 0, 40));
	plane.material.color = ft_color(0.5, 1, 0.1);
	plane.material.diffuse = 0.7;
	plane.material.specular = 0.3;

	plane2 = ft_plane();
	plane2.transform = ft_matrix_multiply(ft_matrix_rotation_y(M_PI / 4), ft_matrix_translation(0, 0, 50));
	plane2.material.color = ft_color(0.2, 1, 0.1);
	plane2.material.diffuse = 0.7;
	plane2.material.specular = 0.3;

	middle = ft_create_sphere();
	middle.transform = ft_matrix_translation(-0.5, 1, 0.5);
	middle.material = ft_material();
	middle.material.color = ft_color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	printf("middle\n");

	right = ft_create_sphere();
	right.transform = ft_matrix_multiply(ft_matrix_translation(1.5, 0.5, -0.5), ft_matrix_scaling(0.5, 0.5, 0.5));
	right.material = ft_material();
	right.material.color = ft_color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;
	printf("right\n");

	left = ft_create_sphere();
	left.transform = ft_matrix_multiply(ft_matrix_translation(-1.5, 0.33, -0.75), ft_matrix_scaling(0.33, 0.33, 0.33));
	left.material = ft_material();
	left.material.color = ft_color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;
	printf("left\n");

	cyl = ft_cylinder();
	cyl.transform = ft_matrix_multiply(ft_matrix_multiply(ft_matrix_translation(0.5, 0, -0.5), ft_matrix_scaling(0.5, 0.5, 0.5)), ft_matrix_rotation_x(M_PI / 4 * -1));
	cyl.material.color = ft_color(0, 1, 0);
	cyl.material.diffuse = 0.7;
	cyl.material.specular = 0.3;
	cyl.closed = 1;
	cyl.minimum = 1;
	cyl.maximum = 3;

	light = ft_point_light(ft_create_point(-10, 10, -10), ft_color(1, 1, 1));
	world = ft_world();
	world = ft_world_add_light(world, light);
	world = ft_world_add_sphere(world, middle);
	world = ft_world_add_sphere(world, right);
	world = ft_world_add_sphere(world, left);
	world = ft_world_add_sphere(world, plane);
	world = ft_world_add_sphere(world, plane2);
	world = ft_world_add_sphere(world, cyl);

	printf("world\n");
	printf("%i %i\n", world.n_lights, world.n_spheres);
	printf("%f %f %f %f\n", world.lights[0].position.x, world.lights[0].position.y, world.lights[0].position.z, world.lights[0].position.w);
	printf("%f %f %f\n", world.lights[0].intensity.red, world.lights[0].intensity.green, world.lights[0].intensity.blue);

	camera = ft_camera(20000, 10000, M_PI/3);
	camera.transform = ft_view_transform(ft_create_point(0, 1.5, -5), ft_create_point(0, 1, 0), ft_create_vector(0, 1, 0));
	printf("camera\n");
	ft_print_matrix(camera.transform);

	canvas = ft_render(camera, world);
	printf("render\n");
	ft_canvas_to_ppm(canvas);
	printf("ppm\n");

	ft_free_canvas(canvas);
	free(world.spheres);
	free(world.lights);
	
	return (0);
}*/

/*
int	main(void)
{
	t_shape cyl = ft_cylinder();
	cyl.minimum = 1;
	cyl.maximum = 2;
	cyl.closed = 1;
	t_tuple	n = ft_normal_at_cylinder(cyl, ft_create_point(0, 1, 0));
	printf("%f %f %f %f\n", n.x, n.y, n.z, n.w);
	n = ft_normal_at_cylinder(cyl, ft_create_point(0.5, 1, 0));
	printf("%f %f %f %f\n", n.x, n.y, n.z, n.w);
	n = ft_normal_at_cylinder(cyl, ft_create_point(0, 1, 0.5));
	printf("%f %f %f %f\n", n.x, n.y, n.z, n.w);
	n = ft_normal_at_cylinder(cyl, ft_create_point(0, 2, 0));
	printf("%f %f %f %f\n", n.x, n.y, n.z, n.w);
	n = ft_normal_at_cylinder(cyl, ft_create_point(0.5, 2, 0));
	printf("%f %f %f %f\n", n.x, n.y, n.z, n.w);
	n = ft_normal_at_cylinder(cyl, ft_create_point(0, 2, 0.5));
	printf("%f %f %f %f\n", n.x, n.y, n.z, n.w);
	return (0);
}*/

/*
int	main(void)
{
	t_shape cyl = ft_cylinder();
	cyl.minimum = 1;
	cyl.maximum = 2;
	cyl.closed = 1;
	t_tuple	direction = ft_tuple_normalize(ft_create_vector(0, -1, 0));
	t_ray	r = ft_ray(ft_create_point(0, 3, 0), direction);
	t_intersections xs = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs.count);

	direction = ft_tuple_normalize(ft_create_vector(0, -1, 2));
	r = ft_ray(ft_create_point(0, 3, -2), direction);
	t_intersections xs2 = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs2.count);

	direction = ft_tuple_normalize(ft_create_vector(0, -1, 1));
	r = ft_ray(ft_create_point(0, 4, -2), direction);
	t_intersections xs3 = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs3.count);

	direction = ft_tuple_normalize(ft_create_vector(0, 1, 2));
	r = ft_ray(ft_create_point(0, 0, -2), direction);
	t_intersections xs4 = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs4.count);

	direction = ft_tuple_normalize(ft_create_vector(0, 1, 1));
	r = ft_ray(ft_create_point(0, -1, -2), direction);
	t_intersections xs5 = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs5.count);

	return (0);
}*/

/*
int	main(void)
{
	t_shape cyl = ft_cylinder();
	cyl.minimum = 1;
	cyl.maximum = 2;
	t_tuple	direction = ft_tuple_normalize(ft_create_vector(0.1, 1, 0));
	t_ray	r = ft_ray(ft_create_point(0, 1.5, 0), direction);
	t_intersections xs = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs.count);

	direction = ft_tuple_normalize(ft_create_vector(0, 0, 1));
	r = ft_ray(ft_create_point(0, 3, -5), direction);
	t_intersections xs2 = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs2.count);

	direction = ft_tuple_normalize(ft_create_vector(0, 0, 1));
	r = ft_ray(ft_create_point(0, 0, -5), direction);
	t_intersections xs3 = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs3.count);

	direction = ft_tuple_normalize(ft_create_vector(0, 0, 1));
	r = ft_ray(ft_create_point(0, 2, -5), direction);
	t_intersections xs4 = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs4.count);

	direction = ft_tuple_normalize(ft_create_vector(0, 0, 1));
	r = ft_ray(ft_create_point(0, 1, -5), direction);
	t_intersections xs5 = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs5.count);

	direction = ft_tuple_normalize(ft_create_vector(0, 0, 1));
	r = ft_ray(ft_create_point(0, 1.5, -2), direction);
	t_intersections xs6 = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs6.count);

	return (0);
}*/

/*
int	main(void)
{
	t_shape	cyl = ft_cylinder();
	t_tuple	n = ft_normal_at_cylinder(ft_create_point(1, 0, 0));
	printf("%f %f %f %f\n", n.x, n.y, n.z, n.w);

	cyl = ft_cylinder();
	n = ft_normal_at_cylinder(ft_create_point(0, 5, -1));
	printf("%f %f %f %f\n", n.x, n.y, n.z, n.w);

	cyl = ft_cylinder();
	n = ft_normal_at_cylinder(ft_create_point(0, -2, 1));
	printf("%f %f %f %f\n", n.x, n.y, n.z, n.w);

	cyl = ft_cylinder();
	n = ft_normal_at_cylinder(ft_create_point(-1, 1, 0));
	printf("%f %f %f %f\n", n.x, n.y, n.z, n.w);
}*/


/*
int	main(void)
{
	t_shape	cyl = ft_cylinder();
	t_tuple direction = ft_tuple_normalize(ft_create_vector(0, 0, 1));
	t_ray	r = ft_ray(ft_create_point(1, 0, -5), direction);
	t_intersections	xs = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs.count);
	printf("%f %f\n", xs.xs[0].t, xs.xs[1].t);

	cyl = ft_cylinder();
	direction = ft_tuple_normalize(ft_create_vector(0, 0, 1));
	r = ft_ray(ft_create_point(0, 0, -5), direction);
	xs = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs.count);
	printf("%f %f\n", xs.xs[0].t, xs.xs[1].t);

	cyl = ft_cylinder();
	direction = ft_tuple_normalize(ft_create_vector(0.1, 1, 1));
	r = ft_ray(ft_create_point(0.5, 0, -5), direction);
	xs = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs.count);
	printf("%f %f\n", xs.xs[0].t, xs.xs[1].t);

	
	return (0);
}*/


/*CYLINDROS*//*
int	main(void)
{
	t_shape	cyl = ft_cylinder();
	t_tuple	direction = ft_tuple_normalize(ft_create_vector(0, 1, 0));
	t_ray	r = ft_ray(ft_create_point(1, 0, 0), direction);
	t_intersections xs = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs.count);

	cyl = ft_cylinder();
	direction = ft_tuple_normalize(ft_create_vector(0, 1, 0));
	r = ft_ray(ft_create_point(0, 0, 0), direction);
	xs = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs.count);

	cyl = ft_cylinder();
	direction = ft_tuple_normalize(ft_create_vector(1, 1, 1));
	r = ft_ray(ft_create_point(0, 0, -5), direction);
	xs = ft_cylinders_intersect(cyl, r);
	printf("%i\n", xs.count);

	return (0);
}*/

/*
int	main(void)
{
	t_canvas	canvas;
	t_world		world;
	t_camera	camera;
	t_shape		middle;
	t_shape		right;
	t_shape		left;
	t_light		light;
	t_shape		plane;
	t_shape		plane2;

	plane = ft_plane();
	plane.transform = ft_matrix_multiply(ft_matrix_rotation_x(M_PI / 2), ft_matrix_translation(0, 0, 40));
	plane.material.color = ft_color(0.5, 1, 0.1);
	plane.material.diffuse = 0.7;
	plane.material.specular = 0.3;

	plane2 = ft_plane();
	plane2.transform = ft_matrix_multiply(ft_matrix_rotation_y(M_PI / 4), ft_matrix_translation(0, 0, 50));
	plane2.material.color = ft_color(0.2, 1, 0.1);
	plane2.material.diffuse = 0.7;
	plane2.material.specular = 0.3;

	middle = ft_create_sphere();
	middle.transform = ft_matrix_translation(-0.5, 1, 0.5);
	middle.material = ft_material();
	middle.material.color = ft_color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	printf("middle\n");

	right = ft_create_sphere();
	right.transform = ft_matrix_multiply(ft_matrix_translation(1.5, 0.5, -0.5), ft_matrix_scaling(0.5, 0.5, 0.5));
	right.material = ft_material();
	right.material.color = ft_color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;
	printf("right\n");

	left = ft_create_sphere();
	left.transform = ft_matrix_multiply(ft_matrix_translation(-1.5, 0.33, -0.75), ft_matrix_scaling(0.33, 0.33, 0.33));
	left.material = ft_material();
	left.material.color = ft_color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;
	printf("left\n");

	light = ft_point_light(ft_create_point(-10, 10, -10), ft_color(1, 1, 1));
	world = ft_world();
	world = ft_world_add_light(world, light);
	world = ft_world_add_sphere(world, middle);
	world = ft_world_add_sphere(world, right);
	world = ft_world_add_sphere(world, left);
	world = ft_world_add_sphere(world, plane);
	world = ft_world_add_sphere(world, plane2);
	printf("world\n");
	printf("%i %i\n", world.n_lights, world.n_spheres);
	printf("%f %f %f %f\n", world.lights[0].position.x, world.lights[0].position.y, world.lights[0].position.z, world.lights[0].position.w);
	printf("%f %f %f\n", world.lights[0].intensity.red, world.lights[0].intensity.green, world.lights[0].intensity.blue);

	camera = ft_camera(1000, 500, M_PI/3);
	camera.transform = ft_view_transform(ft_create_point(0, 1.5, -5), ft_create_point(0, 1, 0), ft_create_vector(0, 1, 0));
	printf("camera\n");
	ft_print_matrix(camera.transform);

	canvas = ft_render(camera, world);
	printf("render\n");
	ft_canvas_to_ppm(canvas);
	printf("ppm\n");
	return (0);
}*/

/*
int	main(void)
{
	t_shape	p = ft_plane();
	t_ray	r = ft_ray(ft_create_point(0, 10, 0), ft_create_vector(0, 0, 1));
	t_intersections	xs = ft_intersect(&p, r);
	printf("%i\n", xs.count);

	p = ft_plane();
	r = ft_ray(ft_create_point(0, 0, 0), ft_create_vector(0, 0, 1));
	xs = ft_intersect(&p, r);
	printf("%i\n", xs.count);

	p = ft_plane();
	r = ft_ray(ft_create_point(0, 1, 0), ft_create_vector(0, -1, 0));
	xs = ft_intersect(&p, r);
	printf("%i\n", xs.count);

	p = ft_plane();
	r = ft_ray(ft_create_point(0, -1, 0), ft_create_vector(0, 1, 0));
	xs = ft_intersect(&p, r);
	printf("%i\n", xs.count);

	return (0);
}*/

/*
int	main(void)
{
	t_shape p;

	p = ft_plane();
	t_tuple n1 = ft_normal_at(p, ft_create_point(0, 0, 0));
	t_tuple n2 = ft_normal_at(p, ft_create_point(10, 0, -10));
	t_tuple n3 = ft_normal_at(p, ft_create_point(-5, 0, 150));
	printf("%f %f %f %f\n", n1.x, n1.y, n1.z, n1.w);
	printf("%f %f %f %f\n", n2.x, n2.y, n2.z, n2.w);
	printf("%f %f %f %f\n", n3.x, n3.y, n3.z, n3.w);
	return (0);
}*/

/*
int	main(void)
{
	t_shape		s;
	t_tuple		n;
	t_matrix	m;

	s = ft_test_shape();
	ft_set_transform(&s, ft_matrix_translation(0, 1, 0));
	n = ft_normal_at(s, ft_create_point(0, 1.70711, -0.70711));
	printf("%f %f %f %f\n",n.x, n.y, n.z, n.w);

	s = ft_test_shape();
	m = ft_matrix_multiply(ft_matrix_scaling(1, 0.5, 1), ft_matrix_rotation_z(M_PI / 5));
	ft_set_transform(&s, m);
	n = ft_normal_at(s, ft_create_point(0, sqrtf(2) / 2, sqrtf(2) / 2 * -1));
	printf("%f %f %f %f\n",n.x, n.y, n.z, n.w);
	return (0);
}*/

/*
int	main(void)
{
	t_ray	r = ft_ray(ft_create_point(0, 0, -5), ft_create_vector(0, 0, 1));
	t_shape	s = ft_test_shape();
	ft_set_transform(&s, ft_matrix_scaling(2, 2, 2));
	t_intersections xs = ft_intersect(&s, r);
	printf("%f %f %f %f\n", s.saved_ray.origin.x, s.saved_ray.origin.y, s.saved_ray.origin.z, s.saved_ray.origin.w);
	printf("%f %f %f %f\n", s.saved_ray.direction.x, s.saved_ray.direction.y, s.saved_ray.direction.z, s.saved_ray.direction.w);
	
	t_ray	r2 = ft_ray(ft_create_point(0, 0, -5), ft_create_vector(0, 0, 1));
	t_shape	s2 = ft_test_shape();
	ft_set_transform(&s2, ft_matrix_translation(5, 0, 0));
	t_intersections xs2 = ft_intersect(&s2, r2);
	printf("%f %f %f %f\n", s2.saved_ray.origin.x, s2.saved_ray.origin.y, s2.saved_ray.origin.z, s2.saved_ray.origin.w);
	printf("%f %f %f %f\n", s2.saved_ray.direction.x, s2.saved_ray.direction.y, s2.saved_ray.direction.z, s2.saved_ray.direction.w);
	
	return (0);
}*/

/*
int	main(void)
{
	t_ray r = ft_ray(ft_create_point(0,0,-5), ft_create_vector(0,0,1));
	t_sphere shape = ft_create_sphere();
	ft_sphere_set_transform(shape, ft_matrix_translation(0,0,1));
	t_intersection i = ft_intersection(5, shape);
	t_comps comps = ft_prepare_computations(i, r);
	printf("%f < %f\n", comps.over_point.z, 0.00001 * -1 /2);
	printf("%f > %f\n", comps.point.z, comps.over_point.z);

	return (0);
}*/


/*
int	main(void)
{
	t_world w = ft_world();
	w = ft_world_add_light(w, ft_point_light(ft_create_point(0,0,-10), ft_color(1,1,1)));
	t_sphere s1 = ft_create_sphere();
	w = ft_world_add_sphere(w, s1);
	t_sphere s2 = ft_create_sphere();
	ft_sphere_set_transform(s2, ft_matrix_translation(0,0,10));
	w = ft_world_add_sphere(w, s2);
	t_ray r = ft_ray(ft_create_point(0,0,5), ft_create_vector(0,0,1));
	t_intersection i = ft_intersection(4, s2);
	t_comps comps = ft_prepare_computations(i, r);
	t_color c = ft_shade_hit(w, comps);
	printf("%f %f %f\n", c.red, c.green, c.blue);

	return (0);
}*/

/*
int	main(void)
{
	t_world	w = ft_default_world();
	t_tuple	p = ft_create_point(0, 10, 0);

	printf("%i\n", ft_is_shadowed(w, p));
	return (0);
}*/

/*
int	main(void)
{
	t_tuple	eyev = ft_create_vector(0,0,-1);
	t_tuple	normalv = ft_create_vector(0,0,-1);
	t_light	light = ft_point_light(ft_create_point(0,0,-10), ft_color(1,1,1));
	int		in_shadow = 1;
	t_color	c;
	t_material	m;
	t_tuple		position;

	m = ft_material();
	position = ft_create_point(0,0,0);
	c = ft_lighting(m, light, position, eyev, normalv, in_shadow);
	printf("%f %f %f\n", c.red, c.green, c.blue);

	return (0);
}*/

/*
int	main(void)
{
	t_material	m;
	t_tuple		eyev;
	t_tuple		normalv;
	t_light		light;
	t_color		c1;
	t_color		c2;

	m.pattern = ft_stripe_pattern(ft_color(1, 1, 1), ft_color(0,0,0));
	m.ambient = 1;
	m.diffuse = 0;
	m.specular = 0;
	m.has_pattern = 1;
	eyev = ft_create_vector(0, 0, -1);
	normalv = ft_create_vector(0, 0, -1);
	light = ft_point_light(ft_create_point(0,0,-10), ft_color(1,1,1));
	c1 = ft_lighting(m, light, ft_create_point(0.9, 0, 0), eyev, normalv);
	c2 = ft_lighting(m, light, ft_create_point(1.1, 0, 0), eyev, normalv);
	printf("%f %f %f\n", c1.red, c1.green, c1.blue);
	printf("%f %f %f\n", c2.red, c2.green, c2.blue);
}*/

/*
int	main(void)
{
	t_pattern	pattern;
	t_color		c;

	pattern = ft_stripe_pattern(ft_color(1,1,1), ft_color(0,0,0));
	c = ft_stripe_at(pattern, ft_create_point(0,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_stripe_at(pattern, ft_create_point(0.9,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_stripe_at(pattern, ft_create_point(1,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_stripe_at(pattern, ft_create_point(-0.1,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_stripe_at(pattern, ft_create_point(-1,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
	c = ft_stripe_at(pattern, ft_create_point(-1.1,0,0));
	printf("%f %f %f\n", c.red, c.green, c.blue);
}*/

/*
int	main(void)
{
	t_canvas	canvas;
	t_world		world;
	t_camera	camera;
	t_shape		floor;
	t_shape		left_wall;
	t_shape		right_wall;
	t_shape		middle;
	t_shape		right;
	t_shape		left;
	t_light		light;

	floor = ft_create_sphere();
	floor.transform = ft_matrix_scaling(10, 0.01, 10);
	floor.material = ft_material();
	floor.material.color = ft_color(1, 0.9, 0.9);
	floor.material.specular = 0;
	printf("floor\n");

	left_wall = ft_create_sphere();
	left_wall.transform = 	ft_matrix_multiply(
							ft_matrix_multiply(
							ft_matrix_multiply(
								ft_matrix_translation(0,0,5),
								ft_matrix_rotation_y(M_PI*-1/4)),
								ft_matrix_rotation_x(M_PI/2)),
			  					ft_matrix_scaling(10, 0.01, 10));
	left_wall.material = floor.material;
	printf("left_wall\n");

	right_wall = ft_create_sphere();
	right_wall.transform = ft_matrix_multiply(
							ft_matrix_multiply(
							ft_matrix_multiply(
								ft_matrix_translation(0,0,5),
								ft_matrix_rotation_y(M_PI/4)),
								ft_matrix_rotation_x(M_PI/2)),
			  					ft_matrix_scaling(10, 0.01, 10));
	right_wall.material = floor.material;
	printf("right_wall\n");

	middle = ft_create_sphere();
	middle.transform = ft_matrix_translation(-0.5, 1, 0.5);
	middle.material = ft_material();
	middle.material.color = ft_color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	printf("middle\n");

	right = ft_create_sphere();
	right.transform = ft_matrix_multiply(ft_matrix_translation(1.5, 0.5, -0.5), ft_matrix_scaling(0.5, 0.5, 0.5));
	right.material = ft_material();
	right.material.color = ft_color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;
	printf("right\n");

	left = ft_create_sphere();
	left.transform = ft_matrix_multiply(ft_matrix_translation(-1.5, 0.33, -0.75), ft_matrix_scaling(0.33, 0.33, 0.33));
	left.material = ft_material();
	left.material.color = ft_color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;
	printf("left\n");

	light = ft_point_light(ft_create_point(-10, 10, -10), ft_color(1, 1, 1));
	world = ft_world();
	world = ft_world_add_light(world, light);
	world = ft_world_add_sphere(world, floor);
	world = ft_world_add_sphere(world, left_wall);
	world = ft_world_add_sphere(world, right_wall);
	world = ft_world_add_sphere(world, middle);
	world = ft_world_add_sphere(world, right);
	world = ft_world_add_sphere(world, left);
	printf("world\n");
	printf("%i %i\n", world.n_lights, world.n_spheres);
	printf("%f %f %f %f\n", world.lights[0].position.x, world.lights[0].position.y, world.lights[0].position.z, world.lights[0].position.w);
	printf("%f %f %f\n", world.lights[0].intensity.red, world.lights[0].intensity.green, world.lights[0].intensity.blue);

	camera = ft_camera(600, 300, M_PI/3);
	camera.transform = ft_view_transform(ft_create_point(0, 1.5, -5), ft_create_point(0, 1, 0), ft_create_vector(0, 1, 0));
	printf("camera\n");

	canvas = ft_render(camera, world);
	printf("render\n");
	ft_canvas_to_ppm(canvas);
	printf("ppm\n");
	return (0);
}*/

/*
int	main(void)
{
	t_world		w;
	t_camera	c;
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_canvas	image;
	t_color		color;
	

	w = ft_default_world();
	c = ft_camera(11, 11, M_PI/2);
	from = ft_create_point(0, 0, -5);
	to = ft_create_point(0, 0, 0);
	up = ft_create_vector(0, 1, 0);
	c.transform = ft_view_transform(from, to, up);
	image = ft_render(c, w);
	color = image.pixel[5][5];
	printf("%f %f %f\n", color.red, color.green, color.blue);
	return (0);
}*/

/*
int main(void)
{
	t_camera	c;
	t_ray		r;

	c = ft_camera(201, 101, M_PI/2);
	r = ft_ray_for_pixel(c, 100, 50);
	printf("origin->   \t%f %f %f %f\n", r.origin.x, r.origin.y, r.origin.z, r.origin.w);
	printf("direction->\t%f %f %f %f\n", r.direction.x, r.direction.y, r.direction.z, r.direction.w);
	c = ft_camera(201, 101, M_PI/2);
	r = ft_ray_for_pixel(c, 0, 0);
	printf("origin->   \t%f %f %f %f\n", r.origin.x, r.origin.y, r.origin.z, r.origin.w);
	printf("direction->\t%f %f %f %f\n", r.direction.x, r.direction.y, r.direction.z, r.direction.w);
	c = ft_camera(201, 101, M_PI/2);
	c.transform = ft_matrix_multiply(ft_matrix_rotation_y(M_PI/4), ft_matrix_translation(0, -2, 5));
	r = ft_ray_for_pixel(c, 100, 50);
	printf("origin->   \t%f %f %f %f\n", r.origin.x, r.origin.y, r.origin.z, r.origin.w);
	printf("direction->\t%f %f %f %f\n", r.direction.x, r.direction.y, r.direction.z, r.direction.w);
	
	return (0);
}*/

/*
int	main(void)
{
	t_matrix	m;
	int			x;
	int			y;
	m = ft_view_transform(ft_create_point(1, 3, 2), ft_create_point(4, -2, 8), ft_create_vector(1, 1, 0));
	y = 0;
	while (y < m.rows)
	{
		x = 0;
		while (x < m.cols)
		{
			printf("%f\t", m.data[y][x]);
			x++;
		}
		y++;
		printf("\n");
	}
	
	return (0);
}*/

/*
int	main(void)
{
	t_world	w;
	t_ray	r;
	t_color	c;

	w = ft_world();
	r = ft_ray(ft_create_point(0,0,-5), ft_create_vector(0,0,1));
	c = ft_color_at(w, r);
	printf("%f %f %f\n", c.red, c.green, c.blue);
	return (0);
}*/

/*
int	main(void)
{
	t_world		w;
	t_ray		r;
	t_sphere	shape;
	t_intersection i;
	t_comps		comps;
	t_color		color;
	t_light		l;

	w = ft_world();
	l = ft_point_light(ft_create_point(0, 0.25, 0), ft_color(1, 1, 1));
	r = ft_ray(ft_create_point(0,0,0), ft_create_vector(0,0,1));
	w = ft_world_add_light(w, l);
	shape = ft_create_sphere();
	shape.material.color = ft_color(0.8, 1, 0.6);
	shape.material.diffuse = 0.7;
	shape.material.specular = 0.2;
	w = ft_world_add_sphere(w, shape);
	i = ft_intersection(0.5, shape);
	comps = ft_prepare_computations(i, r);
	color = ft_shade_hit(w, comps);
	printf("%f %f %f\n", color.red, color.green, color.blue);
	return (0);
}*/

/*
int	main(void)
{
	t_ray			ray;
	t_sphere		shape;
	t_intersection	inter;
	t_comps			comps;

	ray = ft_ray(ft_create_point(0, 0, -5), ft_create_vector(0, 0, 1));
	shape = ft_create_sphere();
	inter = ft_intersection(4, shape);
	comps = ft_prepare_computations(inter, ray);
	printf("%i\n", comps.inside);
	printf("%f %f %f %f\n", comps.normalv.x, comps.normalv.y, comps.normalv.z, comps.normalv.w);
	return (0);
}*/

/*
int	main(void)
{
	t_light		light;
	t_sphere	s1;
	t_sphere	s2;
	t_world		world;
	t_ray		ray;
	t_intersections	xs;
	int			i;
	t_color		c;

	light = ft_point_light(ft_create_point(-10, 10, -10), ft_color(1,1,1));
	s1 = ft_create_sphere();
	s1.material.color = ft_color(0.8, 1, 0.6);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.2;
	s1.material.ambient = 1;
	s2 = ft_create_sphere();
	s2.transform = ft_matrix_scaling(0.5, 0.5, 0.5);
	s2.material.color = ft_color(0.21,0.22,0.99);
	s2.material.ambient = 1;
	world = ft_world();
	world = ft_world_add_light(world, light);
	world = ft_world_add_sphere(world, s1);
	world = ft_world_add_sphere(world, s2);
	ft_sphere_print(world.spheres[0]);
	ft_sphere_print(world.spheres[1]);
	ray = ft_ray(ft_create_point(0, 0, 0.75), ft_create_vector(0, 0, -1));
	xs = ft_intersect_world(world, ray);
	printf("%i\n", xs.count);
	i = 0;
	while (i < xs.count)
	{
		printf("%f\n",xs.xs[i].t);
		i++;
	}
	c = ft_color_at(world, ray);
	printf("%f %f %f\n", c.red, c.green, c.blue);
	return (0);
}*/


/*
int	main(void)
{
	t_tuple		ray_origin;
	int			canvas_pixels;
	float		wall_size;
	t_canvas	canvas;
	float		pixel_size;
	float		half;
	t_color		color;
	t_sphere	shape;
	int			y;
	float		world_y;
	int			x;
	float		world_x;
	float		wall_z;
	t_tuple		position;
	t_ray		r;
	t_intersections	xs;
	t_light		light;

	ray_origin = ft_create_point(0, 0, -5);
	wall_z = 10;
	wall_size = 7;
	canvas_pixels = 1000;
	pixel_size = wall_size / canvas_pixels;
	half = wall_size / 2;

	canvas = ft_canvas(canvas_pixels, canvas_pixels);
	color = ft_color(1, 0, 0);
	shape = ft_create_sphere();
	shape.material = ft_material();
	shape.material.color = ft_color(1, 0.2, 1);
	light = ft_point_light(ft_create_point(-10, 10, -10), ft_color(1, 1, 1));
	y = 0;
	while (y < canvas_pixels - 1)
	{
		world_y = half - (pixel_size * y);
		x = 0;
		while (x < canvas_pixels - 1)
		{
			world_x = (half * -1) + pixel_size * x;
			position = ft_create_point(world_x, world_y, wall_z);
			r = ft_ray(ray_origin, ft_tuple_normalize(ft_subtract_tuples(position, ray_origin)));
			xs = ft_sphere_intersect(shape, r);
			if (xs.count > 0 && ft_hit(xs).t != -1)
			{
				t_tuple	point;
				t_tuple	normal;
				t_tuple	eye;
				t_intersection	hit;

				hit = ft_hit(xs);
				point = ft_ray_position(r, hit.t);
				normal = ft_normal_at(hit.object, point);
				eye = ft_multiply_tuple(r.direction, -1);
				color = ft_lighting(hit.object.material, light, point, eye, normal);
				ft_write_pixel(canvas, x, y, color);
			}
			x++;
		}
		y++;
	}
	ft_canvas_to_ppm(canvas);
	return (0);
}*/


/*
int	main(void)
{
	t_tuple		ray_origin;
	int			canvas_pixels;
	float		wall_size;
	t_canvas	canvas;
	float		pixel_size;
	float		half;
	t_color		color;
	t_sphere	shape;
	int			y;
	float		world_y;
	int			x;
	float		world_x;
	float		wall_z;
	t_tuple		position;
	t_ray		r;
	t_intersections	xs;

	ray_origin = ft_create_point(0, 0, -5);
	wall_z = 10;
	wall_size = 7;
	canvas_pixels = 100;
	pixel_size = wall_size / canvas_pixels;
	half = wall_size / 2;

	canvas = ft_canvas(canvas_pixels, canvas_pixels);
	color = ft_color(1, 0, 0);
	shape = ft_create_sphere();
	y = 0;
	while (y < canvas_pixels - 1)
	{
		world_y = half - (pixel_size * y);
		x = 0;
		while (x < canvas_pixels - 1)
		{
			world_x = (half * -1) + pixel_size * x;
			position = ft_create_point(world_x, world_y, wall_z);
			r = ft_ray(ray_origin, ft_tuple_normalize(ft_subtract_tuples(position, ray_origin)));
			xs = ft_sphere_intersect(shape, r);
			if (xs.count > 0 && ft_hit(xs).t != -1)
			{
				ft_write_pixel(canvas, x, y, color);
			}
			x++;
		}
		y++;
	}
	ft_canvas_to_ppm(canvas);
	return (0);
}*/



/*
int	main(void)
{
	t_material	m;
	t_tuple		position;
	t_tuple		eyev;
	t_tuple		normalv;
	t_light		light;
	t_color		result;

	m = ft_material();
	position = ft_create_point(0, 0, 0);

	eyev = ft_create_vector(0, 0 , -1);
	normalv = ft_create_vector(0, 0, -1);
	light = ft_point_light(ft_create_point(0, 0, 10), ft_color(1, 1, 1));
	result = ft_lighting(m, light, position, eyev, normalv);
	printf("result\t%f %f %f\n", result.red, result.green, result.blue);
	return (0);
}*/


/*
int	main(void)
{
	t_tuple v = ft_create_vector(0, -1, 0);
	t_tuple n = ft_create_vector(sqrt(2) / 2, sqrt(2) / 2, 0);
	t_tuple	result = ft_reflect(v, n);
	printf("%f %f %f %f\n", result.x, result.y, result.z, result.w);
	return (0);
}*/

/*
int main(void)
{
	t_sphere    s;
	t_tuple     vector;

	s = ft_create_sphere();
	ft_sphere_set_transform(s, ft_matrix_translation(0, 1, 0));
	vector = ft_normal_at(s, ft_create_point(0, 1.70711, -0.70711));
	printf("%f %f %f %f\n", vector.x, vector.y, vector.z, vector.w);
	return (0);
}
*/
/*
int	main(void)
{
	t_sphere		s;
	t_ray			r;
	t_intersections	i;
	int             j;

	s = ft_create_sphere();
	r = ft_ray(ft_create_point(0,0, -5), ft_create_vector(0,0,1));
	ft_sphere_set_transform(s, ft_matrix_translation(5, 0, 0));
	i = ft_sphere_intersect(s, r);
	printf("%i\n", i.count);
	j = 0;
	while (j < i.count)
	{
		printf("%f \n", i.xs[j].t);
		j++;
	}
	return (0);
}*/

/*
int	main(void)
{
	t_ray		r;
	t_matrix	m;
	t_ray		r2;

	r = ft_ray(ft_create_point(1, 2, 3), ft_create_vector(0, 1, 0));
	//m = ft_matrix_translation(3, 4, 5);
	m = ft_matrix_scaling(2, 3, 4);
	r2 = ft_ray_transform(r, m);
	printf("%f %f %f %f\n", r2.origin.x , r2.origin.y, r2.origin.z, r2.origin.w);
	printf("%f %f %f %f\n", r2.direction.x , r2.direction.y, r2.direction.z, r2.direction.w);
	return (0);
}*/

/*
int	main(void)
{
	t_sphere 		sph;
	t_intersection	i1;
	t_intersection	i2;
	t_intersection	i3;
	t_intersection	i4;
	t_intersections	inter;
	t_intersection	hit;

	sph = ft_create_sphere();
	i1 = ft_intersection(5, sph);
	i2 = ft_intersection(7, sph);
	i3 = ft_intersection(-3, sph);
	i4 = ft_intersection(2, sph);
	inter.count = 0;
	inter = ft_intersections(inter, i1);
	inter = ft_intersections(inter, i2);
	inter = ft_intersections(inter, i3);
	inter = ft_intersections(inter, i4);
	hit = ft_hit(inter);
	printf("%f\n", hit.t);
	return (0);
}*/

/*
int	main(void)
{
	t_sphere 		sph;
	t_intersection	i1;
	t_intersection	i2;
	t_intersections	inter;

	sph = ft_create_sphere();
	i1 = ft_intersection(1, sph);
	i2 = ft_intersection(2, sph);
	inter = ft_intersections(inter, i1);
	inter = ft_intersections(inter, i2);
	printf("%i\n", inter.count);
	printf("%f\n", inter.xs[0].t);
	printf("%f\n", inter.xs[1].t);
	return (0);
}*/

/*
int main(void)
{
	t_sphere sph;
	t_ray   ray;

	sph = ft_create_sphere();
	ray = ft_ray(ft_create_point(0,2,-5), ft_create_vector(0,0,1));
	ft_sphere_intersect(sph, ray);
	return (0);
}*/

/*
int main(void)
{
	t_canvas    c;
	t_color     c1;
	t_color     c2;
	t_color     c3;

	t_projectile    proj;
	t_enviroment    env;

	proj.position = ft_create_point(0, 1, 0);
	proj.velocity = ft_multiply_tuple(ft_tuple_normalize(ft_create_vector(1, 1.8, 0)), 10);

	env.gravity = ft_create_vector(0, -0.1, 0);
	env.velocity = ft_create_vector(-0.01, 0, 0);

	c = ft_canvas(1080, 520);
	c1 = ft_color(1, 0, 0);

	while (proj.position.y > 0)
	{
		ft_write_pixel(c, (int)proj.position.x, (int)proj.position.y,c1);
		ft_tick(env, &proj);
	}
	ft_canvas_to_ppm(c);
}*/

/*
int main(void)
{
	t_matrix    m1;
	t_matrix    m2;
	t_matrix    r;

	m1 = ft_matrix(4, 4);
	m2 = ft_matrix(4, 1);
	m1.data[0][0] = 1;
	m1.data[0][1] = 2;
	m1.data[0][2] = 3;
	m1.data[0][3] = 4;
	m1.data[1][0] = 2;
	m1.data[1][1] = 4;
	m1.data[1][2] = 4;
	m1.data[1][3] = 2;
	m1.data[2][0] = 8;
	m1.data[2][1] = 6;
	m1.data[2][2] = 4;
	m1.data[2][3] = 1;
	m1.data[3][0] = 0;
	m1.data[3][1] = 0;
	m1.data[3][2] = 0;
	m1.data[3][3] = 1;
	m2.data[0][0] = 1;
	m2.data[1][0] = 2;
	m2.data[2][0] = 3;
	m2.data[3][0] = 1;

	r = ft_matrix_multiply(m1, m2);
	printf("%f\n%f\n%f\n%f\n",r.data[0][0],r.data[1][0],r.data[2][0],r.data[3][0]);
	return (0);
}*/

/*
int main(void)
{
	t_canvas    canvas;
	t_matrix    t12;
	t_matrix    t11;
	t_matrix    t10;
	t_matrix    t9;
	t_matrix    t8;
	t_matrix    t7;
	t_matrix    t6;
	t_matrix    t5;
	t_matrix    t4;
	t_matrix    t3;
	t_matrix    t2;
	t_matrix    t1;
	t_matrix    rot;
	t_matrix    scale;

	canvas = ft_canvas(200, 200);
	t12 = ft_matrix(4, 1);
	t12.data[0][0] = 0;
	t12.data[1][0] = 100;
	t12.data[2][0] = 0;
	t12.data[3][0] = 1;
	rot = ft_matrix_rotation_z(3.141516/6);
	scale = ft_matrix_scaling(2,2,0);

	t1 = ft_matrix_multiply(rot, t12);
	t2 = ft_matrix_multiply(rot, t1);
	t3 = ft_matrix_multiply(rot, t2);
	t4 = ft_matrix_multiply(rot, t3);
	t5 = ft_matrix_multiply(rot, t4);
	t6 = ft_matrix_multiply(rot, t5);
	t7 = ft_matrix_multiply(rot, t6);
	t8 = ft_matrix_multiply(rot, t7);
	t9 = ft_matrix_multiply(rot, t8);
	t10 = ft_matrix_multiply(rot, t9);
	t11 = ft_matrix_multiply(rot, t10);

	t1 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t1);
	t2 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t2);
	t3 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t3);
	t4 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t4);
	t5 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t5);
	t6 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t6);
	t7 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t7);
	t8 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t8);
	t9 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t9);
	t10 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t10);
	t11 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t11);
	t12 = ft_matrix_multiply(ft_matrix_translation(100,100,0), t12);

	


	ft_write_pixel(canvas, (size_t)t1.data[0][0], (size_t)t1.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t2.data[0][0], (size_t)t2.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t3.data[0][0], (size_t)t3.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t4.data[0][0], (size_t)t4.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t5.data[0][0], (size_t)t5.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t6.data[0][0], (size_t)t6.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t7.data[0][0], (size_t)t7.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t8.data[0][0], (size_t)t8.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t9.data[0][0], (size_t)t9.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t10.data[0][0], (size_t)t10.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t11.data[0][0], (size_t)t11.data[1][0], ft_color(128, 128, 128));
	ft_write_pixel(canvas, (size_t)t12.data[0][0], (size_t)t12.data[1][0], ft_color(128, 128, 128));

	ft_canvas_to_ppm(canvas);
 return (0);
}*/

/*
int main(void)
{
	t_ray   r;
	t_tuple t;

	r = ft_ray(ft_create_point(2,3,4), ft_create_vector(1,0,0));
	t = ft_ray_position(r, 2.5);
	printf("%f %f %f %f\n",t.x,t.y,t.z,t.w);
	return (0);
}*/

/*




typedef struct s_projectile
{
	t_tuple position;
	t_tuple velocity;
}   t_projectile;

typedef struct s_enviroment
{
	t_tuple velocity;
	t_tuple gravity;
}   t_enviroment;

void    ft_tick(t_enviroment env, t_projectile *proj)
{
	proj->position = ft_add_tuples(proj->position, proj->velocity);
	proj->velocity = ft_add_tuples(proj->velocity, env.gravity);
}
*/