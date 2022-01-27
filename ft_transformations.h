#ifndef FT_TRANSFORMATIONS_H
# define FT_TRANSFORMATIONS_H

#include "ft_definitions.h"
# include "ft_matrices.h"
# include "ft_tuples.h"
# include "ft_rays.h"

t_matrix	ft_matrix_translation(float x, float y, float z);
t_matrix	ft_matrix_scaling(float x, float y, float z);
t_matrix	ft_matrix_rotation_x(float x);
t_matrix	ft_matrix_rotation_y(float y);
t_matrix	ft_matrix_rotation_z(float z);
t_matrix	ft_shearing(t_tuple x, t_tuple y, t_tuple z);
t_tuple     ft_multiply_matrix_tuple(t_matrix m, t_tuple t);
t_ray       ft_ray_transform(t_ray r, t_matrix m);
t_matrix	ft_view_transform(t_tuple from, t_tuple to, t_tuple up);

#endif