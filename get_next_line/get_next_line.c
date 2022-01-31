/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 18:16:48 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/31 19:03:27 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *s)
{
	int		i;
	int		size;
	char	*str;

	if (!s)
		return (NULL);
	size = ft_strlen(s, '\n') + 1;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_cut_content(char *s, char *buff)
{
	int		i;
	char	*str;
	int		init;
	int		size;

	i = 0;
	if (!ft_strchr(s, '\n'))
	{
		ft_free(s);
		return (NULL);
	}
	size = ft_strlen(s, '\0') - ft_strlen(buff, '\0');
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	init = ft_strlen(s, '\n') + 1;
	while (i < size && s[init + i])
	{
		str[i] = s[init + i];
		i++;
	}
	str[i] = '\0';
	ft_free(s);
	return (str);
}

/*Junta las cadenas, inicializa la statica si esta vacia*/
char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	str = malloc(ft_strlen(s1, '\0') + ft_strlen(s2, '\0') + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[j + i] = '\0';
	ft_free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buff;
	ssize_t		size;

	if (fd == 2 || fd < 0)
		return (NULL);
	buff = malloc(sizeof(char) * (100 + 1));
	size = 1;
	while (size > 0 && !ft_strchr(str, '\n'))
	{
		size = read(fd, buff, 100);
		if (size < 0)
			break ;
		buff[size] = '\0';
		str = ft_strjoin(str, buff);
	}
	ft_free(buff);
	if (size < 0)
		return (NULL);
	buff = ft_get_line(str);
	str = ft_cut_content(str, buff);
	if (!size && !ft_strlen(buff, 0))
		return (ft_free(buff));
	return (buff);
}
