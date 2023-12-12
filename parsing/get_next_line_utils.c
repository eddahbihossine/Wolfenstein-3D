/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 23:53:09 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 23:53:28 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			i;
	int			j;
	char		*p;

	i = 0;
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i++] = s2[j];
		j++;
	}
	p[i] = '\0';
	free((void *)s1);
	s1 = NULL;
	return (p);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	l_len;
	char			*p;

	if (!s)
		return (NULL);
	l_len = ft_strlen(s);
	i = 0;
	if (start > l_len)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[start];
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(const char *s1)
{
	int			i;
	size_t		len;
	char		*p;

	i = 0;
	len = ft_strlen(s1);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
static int	check_overflow(unsigned long res, int n)
{
	if (n == 1)
		if (res >= 92233720368547758)
			return (-1);
	if (n == -1)
		if (res >= 92233720368547758)
			return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		n;
	long	result;
	int		overflow;

	i = 0;
	n = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			n = -1;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		overflow = check_overflow(result, n);
		if (overflow != 1)
			return (overflow);
		result = (result * 10) + str[i] - 48;
		i++;
	}
	return ((result * n));
}

