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
}

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
			xs = ft_intersect(shape, r);
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
			xs = ft_intersect(shape, r);
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
	ft_set_transform(s, ft_matrix_translation(0, 1, 0));
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
	ft_set_transform(s, ft_matrix_translation(5, 0, 0));
	i = ft_intersect(s, r);
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
	ft_intersect(sph, ray);
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
int ft_compare_float(float n1, float n2)
{
	if (fabs(n1 - n2) < 0.00001)
		return (1);
	else
		return (0);
}



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