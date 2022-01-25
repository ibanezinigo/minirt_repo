#include <math.h>
#include <stdlib.h>
#include <stdio.h>



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





typedef struct s_ray
{
	t_tuple origin;
	t_tuple direction;
}   t_ray;

t_ray   ft_ray(t_tuple origin, t_tuple direction)
{
	t_ray   ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_tuple ft_ray_position(t_ray ray, float t)
{
	return (ft_add_tuples(ray.origin, ft_multiply_tuple(ray.direction, t)));
}

typedef struct  s_sphere
{
	t_tuple 	origin;
	float   	radius;
	t_matrix	transform;
}   t_sphere;

t_sphere    ft_create_sphere()
{
	t_sphere    s;

	s.origin = ft_create_point(0,0,0);
	s.radius = 1;
	s.transform = ft_matrix_translation(0,0,0);
	return (s);
}

t_sphere    ft_create_sphere_translated(t_matrix translation)
{
	t_sphere    s;

	s.origin = ft_create_point(0,0,0);
	s.radius = 1;
	s.transform = ft_matrix_translation(translation.data[0][3],translation.data[1][3],translation.data[2][3]);
	return (s);
}

typedef struct s_intersection
{
	float       t;
	t_sphere    object;
}  t_intersection;


typedef struct s_intersections
{
	int             count;
	t_intersection  *xs;
} t_intersections;

t_ray	ft_ray_transform(t_ray r, t_matrix m);

t_intersections ft_intersect(t_sphere s, t_ray r)
{
	t_intersections inter;
	t_tuple         sph_to_ray;
	float           a;
	float           b;
	float           c;
	float           discrimininant;
	t_ray           nr;

	nr = ft_ray_transform(r, ft_inverse(s.transform));
	sph_to_ray = ft_subtract_tuples(nr.origin, s.origin);
	a = ft_tuple_dot(nr.direction, nr.direction);
	b = 2 * ft_tuple_dot(nr.direction, sph_to_ray);
	c = ft_tuple_dot(sph_to_ray, sph_to_ray) - pow(s.radius, 2);
	discrimininant = (pow(b, 2) - (4 * a * c));
	if (discrimininant < 0)
	{
		inter.count = 0;
		inter.xs = NULL;
		return (inter);
	}
	else
	{
		inter.count = 2;
		inter.xs = malloc(sizeof(t_intersection) * inter.count);
		inter.xs[0].t = (-b - sqrt(discrimininant)) / (2 * a);
		inter.xs[0].object = s;
		inter.xs[1].t = (-b + sqrt(discrimininant)) / (2 * a);
		inter.xs[1].object = s;
		return (inter);
	}
}

t_intersection  ft_intersection(float t, t_sphere s)
{
	t_intersection  i;

	i.t = t;
	i.object = s;
	return (i);
}

t_intersections ft_intersections(t_intersections base, t_intersection inter)
{
	t_intersections intersections;
	int             i; 

	intersections.count = base.count + 1;
	intersections.xs = malloc(sizeof(t_intersection) * intersections.count);
	i = 0;
	while (i < intersections.count - 1)
	{
		intersections.xs[i] = base.xs[i];
		i++;
	}
	intersections.xs[i] = inter;
	return (intersections);
}

t_intersection	ft_hit(t_intersections inter)
{
	int				minpos;
	int				minvalue;
	int				i;
	t_intersection	nul;

	if (inter.count == 0)
	{
		nul.t = -1;
		return (nul);
	}
	minpos = -1;
	minvalue = -1;
	i = 0;
	while (i < inter.count)
	{
		if ((inter.xs[i].t < minvalue || minvalue == -1) && inter.xs[i].t >= 0)
		{
			minpos = i;
			minvalue = inter.xs[i].t;
		}
		i++;
	}
	return (inter.xs[minpos]);
}

t_tuple ft_multiply_matrix_tuple(t_matrix m, t_tuple t)
{
	t_tuple     result;
	t_matrix    origin;
	t_matrix    neworigin;

	origin = ft_matrix(4,1);
	origin.data[0][0] = t.x;
	origin.data[1][0] = t.y;
	origin.data[2][0] = t.z;
	origin.data[3][0] = t.w;
	neworigin = ft_matrix_multiply(m, origin);
	result.x = neworigin.data[0][0];
	result.y = neworigin.data[1][0];
	result.z = neworigin.data[2][0];
	result.w = neworigin.data[3][0];
	ft_matrix_free_data(origin);
	ft_matrix_free_data(neworigin);
	return (result);
}

t_ray	ft_ray_transform(t_ray r, t_matrix m)
{
	t_ray	new_ray;

	new_ray.origin = ft_multiply_matrix_tuple(m, r.origin);
	new_ray.direction = ft_multiply_matrix_tuple(m, r.direction);
	return (new_ray);
}

void	ft_set_transform(t_sphere s, t_matrix translation)
{
	int	x;
	int	y;

	y = 0;
	while (y < s.transform.rows && y < translation.rows)
	{
		x = 0;
		while (x < s.transform.cols && y < translation.cols)
		{
			s.transform.data[y][x] = translation.data[y][x];
			x++;
		}
		y++;
	}
}

t_tuple ft_normal_at(t_sphere s, t_tuple t)
{
	t_tuple object_point;
	t_tuple object_normal;
	t_tuple world_normal;
	t_tuple result;

	object_point = ft_multiply_matrix_tuple(ft_inverse(s.transform), t);
	object_normal = ft_subtract_tuples(object_point, ft_create_point(0, 0, 0));
	world_normal = ft_multiply_matrix_tuple(ft_matrix_transpose(ft_inverse(s.transform)), object_normal);
	world_normal.w = 0;
	result =  ft_tuple_normalize(world_normal);
	return (result);
}

t_tuple	ft_reflect(t_tuple in, t_tuple normal)
{
	t_tuple	reflection;

	reflection = ft_multiply_tuple(ft_multiply_tuple(normal, 2), ft_tuple_dot(in, normal));
	reflection = ft_subtract_tuples(in, reflection);
	return (reflection);
}

typedef struct s_light
{
	t_tuple	position;
	t_tuple	intensity;
}	t_light;

t_light	ft_point_light(t_tuple position, t_tuple intensity)
{
	t_light	light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

typedef	struct s_material
{
	t_color	color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
} t_material;

t_material ft_material()
{
	t_material	m;

	m.color = ft_color(1, 1, 1);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
}

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

