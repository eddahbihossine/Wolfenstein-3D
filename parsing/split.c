/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 06:30:27 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 23:54:05 by abel-hid         ###   ########.fr       */
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
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	if (!set || !s1)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	p = (char *)malloc((end - start + 1) * sizeof(char));
	if (end < start || !p)
		return (NULL);
	while (end > start)
	{
		p[i] = s1[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!(s1[i] || s2[i]))
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}