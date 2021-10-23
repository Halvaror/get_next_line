/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-b <alopez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:00:46 by alopez-b          #+#    #+#             */
/*   Updated: 2021/10/23 12:52:10 by alopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	a;

	a = 0;
	while (s[a])
	{
		a++;
	}
	return (a);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	*ptr;

	if (count == 0 || size == 0)
	{
		size = 1;
		count = 1;
	}
	ptr = malloc (count * size);
	if (!ptr)
		return (NULL);
	ptr = ft_bzero(ptr, count * size);
	return (ptr);
}

void	*ft_bzero(void *str, size_t n)
{
	unsigned int	i;
	unsigned char	*a;

	a = str;
	i = 0;
	while (i < n)
	{
		a[i] = 0;
		i++;
	}
	return (a);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	const char		*s;
	char			*d;

	s = src;
	d = dest;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc ((size + 1 ), sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = (char)s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = (char)s2[j];
		j++;
		i++;
	}
	return (str);
}
