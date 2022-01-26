/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spheres.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:51:59 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/26 18:14:24 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPHERES_H
# define FT_SPHERES_H

#include "ft_matrices.h"
#include "ft_tuples.h"
#include "ft_transformations.h"
#include "ft_materials.h"
#include <stdio.h>

typedef struct  s_sphere
{
	t_tuple 	origin;
	float   	radius;
	t_matrix	transform;
	t_material	material;
}   t_sphere;

t_sphere	ft_create_sphere();
t_sphere	ft_create_sphere_translated(t_matrix translation);
void		ft_set_transform(t_sphere s, t_matrix translation);
t_tuple		ft_normal_at(t_sphere s, t_tuple t);
t_tuple		ft_reflect(t_tuple in, t_tuple normal);
void		ft_sphere_print(t_sphere s);
#endif