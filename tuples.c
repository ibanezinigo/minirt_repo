#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_tuple
{
	float x;
	float y;
	float z;
	float w;
}   t_tuple;

int ft_compare_float(float n1, float n2)
{
	if (fabs(n1 - n2) < 0.00001)
		return (1);
	else
		return (0);
}

t_tuple ft_create_vector(float x, float y, float z)
{
	t_tuple tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = 0;
	return (tuple);
}

t_tuple ft_create_point(float x, float y, float z)
{
	t_tuple tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = 1;
	return (tuple);
}

t_tuple ft_add_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple tuple;

	tuple.x = t1.x + t2.x;
	tuple.y = t1.y + t2.y;
	tuple.z = t1.z + t2.z;
	tuple.w = t1.w + t2.w;
	return (tuple);
}

t_tuple ft_subtract_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple tuple;

	tuple.x = t1.x - t2.x;
	tuple.y = t1.y - t2.y;
	tuple.z = t1.z - t2.z;
	tuple.w = t1.w - t2.w;
	return (tuple);
}

t_tuple ft_multiply_tuple(t_tuple t1, float s)
{
	t_tuple tuple;

	tuple.x = t1.x * (s);
	tuple.y = t1.y * (s);
	tuple.z = t1.z * (s);
	tuple.w = t1.w * (s);
	return (tuple);
}

t_tuple ft_divide_tuple(t_tuple t1, float s)
{
	return (ft_multiply_tuple(t1, 1 / s));
}

t_tuple ft_negate_tuple(t_tuple t1)
{
	return (ft_multiply_tuple(t1, -1));
}

float   ft_tuple_magnitude(t_tuple t)
{
	float result;

	result = 0;
	result += pow(t.x, 2);
	result += pow(t.y, 2);
	result += pow(t.z, 2);
	result += pow(t.w, 2);
	result = sqrt(result);
	return (result);
}

t_tuple ft_tuple_normalize(t_tuple t)
{
	float   magnitude;

	magnitude = ft_tuple_magnitude(t);
	return (ft_divide_tuple(t, magnitude));
}

float ft_tuple_dot(t_tuple t1, t_tuple t2)
{
	float r;

	r = 0;
	r += t1.x * t2.x;
	r += t1.y * t2.y;
	r += t1.z * t2.z;
	r += t1.w * t2.w;
	return (r);
}

t_tuple ft_tuple_cross(t_tuple t1, t_tuple t2)
{
	t_tuple t;

	t.x = t1.y * t2.z - t1.z * t2.y;
	t.y = t1.z * t2.x - t1.x * t2.z;
	t.z = t1.x * t2.y - t1.y * t2.x;
	t.w = t1.w * t2.w - t1.w * t2.w;
	return (t);
}

typedef struct s_color
{
	float red;
	float green;
	float blue;
}   t_color;

t_color ft_color(float r, float g, float b)
{
	t_color color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

t_color ft_color_add(t_color c1, t_color c2)
{
	t_color color;

	color.red = c1.red + c2.red;
	color.green = c1.green + c2.green;
	color.blue = c1.blue + c2.blue;
	return (color);
}

t_color ft_color_subtract(t_color c1, t_color c2)
{
	t_color color;

	color.red = c1.red - c2.red;
	color.green = c1.green - c2.green;
	color.blue = c1.blue - c2.blue;
	return (color);
}

t_color ft_color_multiply_byscalar(t_color c1, float s)
{
	t_color color;

	color.red = c1.red * s;
	color.green = c1.green * s;
	color.blue = c1.blue * s;
	return (color);
}

t_color ft_color_multiply_bycolor(t_color c1, t_color c2)
{
	t_color color;

	color.red = c1.red * c2.red;
	color.green = c1.green * c2.green;
	color.blue = c1.blue * c2.blue;
	return (color);
}

typedef struct s_canvas
{
	size_t  width;
	size_t  height;
	t_color **pixel;
}   t_canvas;

t_canvas ft_canvas(size_t w, size_t h)
{
	t_canvas    canvas;
	int         i;
	int         j;

	canvas.width = w;
	canvas.height = h;
	canvas.pixel = malloc(sizeof(t_color *) * canvas.height);
	i = 0;
	while (i < canvas.width)
	{
		canvas.pixel[i] = malloc(sizeof(t_color) * canvas.width);
		i++;
	}
	i = 0;
	while (i < canvas.height)
	{
		j = 0;
		while (j < canvas.width)
		{
			canvas.pixel[i][j].red = 0;
			canvas.pixel[i][j].green = 0;
			canvas.pixel[i][j].blue = 0;
			j++;
		}
		i++;
	}
	return (canvas);
}

void    ft_write_pixel(t_canvas canvas, size_t x, size_t y, t_color color)
{
	if (x >= canvas.width || x < 0)
		return ;
	if (y >= canvas.height || y < 0)
		return ;
	canvas.pixel[y][x].red = color.red;
	canvas.pixel[y][x].green = color.green;
	canvas.pixel[y][x].blue = color.blue;
}

void    ft_read_pixel(FILE *f, t_canvas canvas, size_t x, size_t y)
{
	if (canvas.pixel[y][x].red < 0)
		fprintf(f, "0 ");
	else if (canvas.pixel[y][x].red > 1)
		fprintf(f, "255 ");
	else
		fprintf(f, "%i ",(int) (canvas.pixel[y][x].red * 255));
	if (canvas.pixel[y][x].green < 0)
		fprintf(f, "0 ");
	else if (canvas.pixel[y][x].green > 1)
		fprintf(f, "255 ");
	else
		fprintf(f, "%i ",(int) (canvas.pixel[y][x].green * 255));
	if (canvas.pixel[y][x].blue < 0)
		fprintf(f, "0");
	else if (canvas.pixel[y][x].blue > 1)
		fprintf(f, "255");
	else
		fprintf(f, "%i",(int) (canvas.pixel[y][x].blue * 255));
}

void    ft_canvas_to_ppm(t_canvas c)
{
	FILE    *f;
	int     w;
	int     h;

	f = fopen("test.ppm", "w+");
	fprintf(f,"P3\n");
	fprintf(f,"%zu %zu\n", c.width, c.height);
	fprintf(f,"255\n");
	h = 0;
	while (h < c.height)
	{
		w = 0;
		while (w < c.width)
		{
			ft_read_pixel(f, c, w, h);
			if (w < (c.width - 1))
				fprintf(f, " ");
			else
				fprintf(f, "\n");
			w++;
		}
		h++;
	}
	fclose(f);
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

typedef struct s_matrix
{
	size_t  rows;
	size_t  cols;
	float   **data;
} t_matrix;

t_matrix    ft_matrix(size_t r, size_t c)
{
	t_matrix    m;
	size_t      i;
	size_t      j;

	m.rows = r;
	m.cols = c;
	m.data = malloc(sizeof(float *) * m.rows);
	i = 0;
	while (i < m.rows)
	{
		m.data[i] = malloc(sizeof(float) * m.cols);
		j = 0;
		while (j < m.cols)
		{
			m.data[i][j] = 0;
			j++;
		}
		i++;
	}
	return (m);
}

void    ft_matrix_free_data(t_matrix m)
{
	int i;

	i = 0;
	while (i < m.rows)
	{
		free(m.data[i]);
		i++;
	}
	free(m.data);
}

int ft_matrix_equals(t_matrix m1, t_matrix m2)
{
	size_t  i;
	size_t  j;

	if (m1.cols != m2.cols || m1.rows != m2.rows)
		return (0);
	i = 0;
	while (i < m1.rows)
	{
		j = 0;
		while (j < m1.cols)
		{
			if (m1.data[i][j] != m2.data[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_matrix ft_matrix_multiply(t_matrix m1, t_matrix m2)
{
	t_matrix    m;
	size_t      i;
	size_t      j;
	size_t      k;

	m = ft_matrix(m1.rows, m2.cols);
	i = 0;
	while (i < m1.rows)
	{
		j = 0;
		while (j < m2.cols)
		{
			m.data[i][j] = 0;
			k = 0;
			while (k < m1.cols)
			{
				m.data[i][j] += m1.data[i][k] * m2.data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (m);
}

t_matrix    ft_matrix_transpose(t_matrix m)
{
	t_matrix    m2;
	size_t      i;
	size_t      j;

	m2 = ft_matrix(m.cols, m.rows);
	i = 0;
	while (i < m.rows)
	{
		j = 0;
		while (j < m.cols)
		{
			m2.data[j][i] = m.data[i][j];
			j++;
		}
		i++;
	}
	return (m2);
}

t_matrix    ft_submatrix(t_matrix m, size_t row, size_t col)
{
	t_matrix    matrix;
	size_t      i;
	size_t      j;
	size_t      r;
	size_t      c;

	matrix = ft_matrix(m.rows - 1, m.cols - 1);
	r = 0;
	c = 0;
	i = 0;
	while (i < m.rows)
	{
		j = 0;
		c = 0;
		while (j < m.cols)
		{
			if (i != row && j != col)
			{
				matrix.data[r][c] = m.data[i][j];
				c++;
			}
			j++;
		}
		if (i != row)
			r++;
		i++;
	}
	return (matrix);
}

float   ft_determinant(t_matrix m);

float   ft_minor(t_matrix m, size_t row, size_t col)
{
	t_matrix    matrix;
	float       result;

	matrix = ft_submatrix(m, row, col);
	//printf("size-> %zu %zu\n", m.cols, matrix.cols);
	result = ft_determinant(matrix);
	ft_matrix_free_data(matrix);
	return (result);
}

float   ft_cofactor(t_matrix m, size_t row, size_t col)
{
	float   result;

	result = ft_minor(m, row, col);
	if (((row + col) % 2) != 0)
	{
		result = result * -1;
	}
	return (result);
}

float   ft_determinant(t_matrix m)
{
	int     i;
	float   result;

	result = 0;
	if (m.rows == 2)
	{
		result = m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
		return (result);
	}
	i = 0;
	while (i < m.cols)
	{
		result += m.data[0][i] * ft_cofactor(m, 0, i);
		i++;
	}
	return (result);
}

t_matrix    ft_inverse(t_matrix m)
{
	float       det;
	t_matrix    matrix;
	size_t      r;
	size_t      c;

	det = ft_determinant(m);
	matrix = ft_matrix(m.rows, m.cols);
	r = 0;
	while (r < m.rows)
	{
		c = 0;
		while (c < m.cols)
		{
			//Swaped c and r to transpose
			matrix.data[c][r] = ft_cofactor(m, r, c) / det;
			c++;
		}
		r++;
	}
	return (matrix);
}


t_matrix    ft_matrix_translation(float x, float y, float z)
{
	t_matrix    trans;

	trans = ft_matrix(4, 4);
	trans.data[0][0] = 1;
	trans.data[1][1] = 1;
	trans.data[2][2] = 1;
	trans.data[3][3] = 1;
	trans.data[0][3] = x;
	trans.data[1][3] = y;
	trans.data[2][3] = z;
	return (trans);
}

t_matrix    ft_matrix_scaling(float x, float y, float z)
{
	t_matrix    trans;

	trans = ft_matrix(4, 4);
	trans.data[0][0] = x;
	trans.data[1][1] = y;
	trans.data[2][2] = z;
	trans.data[3][3] = 1;
	return (trans);
}

t_matrix    ft_matrix_rotation_x(float x)
{
	t_matrix    m;

	m = ft_matrix(4,4);
	m.data[0][0] = 1;
	m.data[3][3] = 1;
	m.data[1][1] = cos((double)x);
	m.data[1][2] = sin((double)x) * -1;
	m.data[2][1] = sin((double)x);
	m.data[2][2] = cos((double)x);
	return (m);
}

t_matrix    ft_matrix_rotation_y(float y)
{
	t_matrix    m;

	m = ft_matrix(4,4);
	m.data[0][0] = cos((double)y);
	m.data[0][2] = sin((double)y);
	m.data[1][1] = 1;
	m.data[2][0] = sin((double)y) * -1;
	m.data[2][2] = cos((double)y);
	m.data[3][3] = 1;
	return (m);
}

t_matrix    ft_matrix_rotation_z(float z)
{
	t_matrix    m;

	m = ft_matrix(4,4);
	m.data[0][0] = cos((double)z);
	m.data[0][1] = sin((double)z) * -1;
	m.data[1][0] = sin((double)z);
	m.data[1][1] = cos((double)z);
	m.data[2][2] = 1;
	m.data[3][3] = 1;
	return (m);
}

t_matrix    ft_shearing(t_tuple x, t_tuple y, t_tuple z)
{
	t_matrix    m;

	m = ft_matrix(4, 4);
	m.data[0][0] = 1;
	m.data[0][1] = x.y;
	m.data[0][2] = x.z;
	m.data[1][0] = y.x;
	m.data[1][1] = 1;
	m.data[1][2] = y.z;
	m.data[2][0] = z.x;
	m.data[2][1] = z.y;
	m.data[2][2] = 1;
	m.data[3][3] = 1;

	return (m);
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
	t_tuple	color;
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

