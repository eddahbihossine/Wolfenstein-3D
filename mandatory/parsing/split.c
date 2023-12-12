/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 06:30:27 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/12 20:28:54 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	ft_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			len++;
			while (*s != '\0' && *s != c)
				s++;
		}
		else
			s++;
	}
	return (len);
}

static int	size_word(char const *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] != c && s[i])
	{
		j++;
		i++;
	}
	return (j);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**p;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	p = (char **)malloc(sizeof(char *) * (ft_len(s, c) + 1));
	if (!p)
		return (NULL);
	while (++j < ft_len(s, c))
	{
		while (s[i] == c)
			i++;
		p[j] = ft_substr(s, i, size_word(s, c, i));
		if (!p[j])
		{
			ft_free(p);
			return (NULL);
		}
		i += size_word(s, c, i);
	}
	p[j] = NULL;
	return (p);
}
