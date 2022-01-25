#ifndef FT_TRANSFORMATIONS_H
#define FT_TRANSFOMATIONS_H

#include "ft_matrices.h"
#include "ft_tuples.h"

t_matrix	ft_matrix_translation(float x, float y, float z);
t_matrix	ft_matrix_scaling(float x, float y, float z);
t_matrix	ft_matrix_rotation_x(float x);
t_matrix	ft_matrix_rotation_y(float y);
t_matrix	ft_matrix_rotation_z(float z);
t_matrix	ft_shearing(t_tuple x, t_tuple y, t_tuple z);

#endif