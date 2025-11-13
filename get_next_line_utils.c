/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andqueir <andreia@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:36:38 by andqueir          #+#    #+#             */
/*   Updated: 2025/11/13 17:47:57 by andqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (((unsigned char)*s) == ((unsigned char)c))
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	int			i;
	char		*join;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = ft_calloc((len +1), sizeof(char));
	if (!join)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		join[len] = s1[len];
		len++;
	}
	i = 0;
	while (s2[i])
	{
		join[len + i] = s2[i];
		i++;
	}
	return (join);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*def;

	def = (unsigned char *) s;
	while (n --)
	{
		*def = '\0';
		def++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (nmemb > (SIZE_MAX / size))
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, (nmemb * size));
	return (mem);
}

size_t	ft_strlen(const char *str)
{
	size_t  i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
