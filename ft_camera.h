#ifndef FT_CAMERA_H
# define FT_CAMERA_H

#include "ft_definitions.h"
#include <math.h>
#include "ft_matrices.h"
#include "ft_tuples.h"
#include "ft_rays.h"
#include "ft_transformations.h"
#include "ft_world.h"
#include "ft_canvas.h"

t_camera	ft_camera(int  h, int v, float field);
t_ray		ft_ray_for_pixel(t_camera cam, float px, float py);
t_canvas	ft_render(t_camera camera, t_world world);
#endif