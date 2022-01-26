
#include "ft_transformations.h"

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

t_matrix	ft_view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_matrix	orientation;
	t_matrix	translation;
	t_matrix	result;
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;

	forward = ft_tuple_normalize(ft_subtract_tuples(to, from));
	left = ft_tuple_cross(forward, ft_tuple_normalize(up));
	true_up = ft_tuple_cross(left, forward);
	orientation = ft_matrix(4, 4);
	orientation.data[0][0] = left.x;
	orientation.data[0][1] = left.y;
	orientation.data[0][2] = left.z;
	orientation.data[0][3] = 0;
	orientation.data[1][0] = true_up.x;
	orientation.data[1][1] = true_up.y;
	orientation.data[1][2] = true_up.z;
	orientation.data[1][3] = 0;
	orientation.data[2][0] = forward.x * -1;
	orientation.data[2][1] = forward.y * -1;
	orientation.data[2][2] = forward.z * -1;
	orientation.data[2][3] = 0;
	orientation.data[3][0] = 0;
	orientation.data[3][1] = 0;
	orientation.data[3][2] = 0;
	orientation.data[3][3] = 1;
	translation = ft_matrix_translation(from.x * -1, from.y * -1, from.z * -1);
	result = ft_matrix_multiply(orientation, translation);
	ft_matrix_free_data(orientation);
	ft_matrix_free_data(translation);
	return (result);
}
