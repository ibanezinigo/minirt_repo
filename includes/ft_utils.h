/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:46:44 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/11 13:19:41 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include <stdlib.h>

double	ft_atof(const char *s);
int		ft_is_rt(char *str);
int		ft_strisspace(char c);
int		ft_strequals(char *s1, char *s2);
int		ft_get_word_aux(char *str, int nword);
char	*ft_get_word(char *str, int nword);
int		ft_strlen(char	*s, char c);
int		ft_is_between(float min, float max, float val);

#endif