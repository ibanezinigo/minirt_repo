/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersections.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:53:34 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/26 19:52:19 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INTERSECTIONS_H
# define FT_INTERSECTIONS_H
# include "ft_spheres.h"
# include "ft_rays.h"
# include "ft_tuples.h"

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

typedef struct s_comps
{
	float		t;
	t_sphere	object;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
	int			inside;
}	t_comps;

t_intersections ft_intersect(t_sphere s, t_ray r);
t_intersection  ft_intersection(float t, t_sphere s);
t_intersections ft_intersections(t_intersections base, t_intersection inter);
t_intersection	ft_hit(t_intersections inter);
t_intersections	ft_add_intersections(t_intersections dest, t_intersections new);
t_comps			ft_prepare_computations(t_intersection inter, t_ray ray);

#endif