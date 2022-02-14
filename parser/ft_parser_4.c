/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:32:59 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/14 13:38:34 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

void	ft_exit_error(int i)
{
	printf("ERROR\nFile Format Error%i.\n", i);
	exit(1);
}

void	ft_validate_color(t_color c)
{
	if (c.red < 0 || c.red > 1)
		ft_exit_error(1);
	if (c.green < 0 || c.green > 1)
		ft_exit_error(2);
	if (c.blue < 0 || c.blue > 1)
		ft_exit_error(3);
}

void	ft_validate_vector(t_tuple v)
{
	if (v.x < -1 || v.x > 1)
		ft_exit_error(4);
	if (v.y < -1 || v.y > 1)
		ft_exit_error(5);
	if (v.z < -1 || v.z > 1)
		ft_exit_error(6);
}

void	ft_notonlynums(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != ','
			&& s[i] != '.' && s[i] != '-')
			ft_exit_error(7);
		i++;
	}
}

void	ft_hassmthng(char *str)
{
	int	i;

	if (ft_strlen(str, '\0') <= 1)
		ft_exit_error(8);
	i = 0;
	if (str[i] == ',')
		i++;
	if (str[i] == '-')
		i++;
	if (str[i] < '0' || str[i] > '9')
		ft_exit_error(9);
}
