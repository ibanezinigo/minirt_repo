/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 18:58:59 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 16:28:50 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "ft_utils.h"

char	*get_next_line(int fd);
int		ft_strlen(char	*str, char c);
char	*ft_strchr(char	*str, char c);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_free(char *s);

#endif
