/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:07:09 by algabrie          #+#    #+#             */
/*   Updated: 2021/09/14 18:07:10 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/api.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static int	ft_size(const char *s)
{
	int	cont;

	cont = 0;
	while (s[cont])
		cont++;
	return (cont);
}

char	*ft_strdup(const char *s)
{
	char	*p;
	int		size;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	size = ft_size(s);
	p = (char *)malloc(size + 1);
	while (size - i)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = 0;
	return (p);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	int		n;
	int		s;

	s = 0;
	n = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (new == NULL)
		return (NULL);
	while (s1 && s1[n] != '\0')
	{
		new[n] = s1[n];
		n++;
	}
	while (s2 && s2[s] != '\0')
	{
		new[n + s] = s2[s];
		s++;
	}
	new[n + s] = '\0';
	return (new);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t destsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (destsize == 0)
		return (srclen);
	while (src[i] != '\0' && i < (destsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*sub;

	i = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start > i)
		return (ft_strdup(""));
	i = ft_strlen(s + start);
	if (len > i)
		len = ft_strlen(s + start);
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

void	add_log(char *log)
{
	int	fd;

	fd = open("logs.log", O_WRONLY | O_APPEND | O_CREAT, 0644);
	write(fd, log, strlen(log));
	close(fd);
}
