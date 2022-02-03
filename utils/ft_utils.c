/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:27:06 by iibanez-          #+#    #+#             */
/*   Updated: 2022/02/03 16:45:59 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

int	ft_strisspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_strequals(char *s1, char *s2)
{
	int	i;

	if (ft_strlen(s1, '\0') != ft_strlen(s2, '\0'))
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_get_word_aux(char *str, int nword)
{
	int	len;
	int	init;

	len = 0;
	init = 0;
	while (len < nword)
	{
		while (str[init] != '\0' && ft_strisspace(str[init]) == 1)
			init++;
		len++;
		if (len < nword)
		{
			while (str[init] != '\0' && ft_strisspace(str[init]) == 0)
				init++;
		}
	}
	return (init);
}

char	*ft_get_word(char *str, int nword)
{
	int		init;
	int		len;
	char	*word;
	int		i;

	init = ft_get_word_aux(str, nword);
	len = 0;
	while (str[init + len] != '\0' && ft_strisspace(str[init + len]) == 0)
		len++;
	word = malloc(sizeof(char) * len + 1);
	i = -1;
	while (++i < len)
		word[i] = str[init + i];
	word[i] = '\0';
	return (word);
}

int	ft_strlen(char	*s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}
