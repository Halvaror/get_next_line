/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-b <alopez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 21:14:21 by alopez-b          #+#    #+#             */
/*   Updated: 2021/10/24 18:59:00 by alopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	check_next_line(char *buff)
{
	ssize_t	i;

	i = 0;
	if (!buff)
		return (-1);
	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*cut_str(char *buff)
{
	ssize_t	r;
	char	*str;

	r = check_next_line(buff);
	if (r == -1)
		return (NULL);
	str = (char *)ft_calloc(sizeof(char), (r + 2));
	if (!str)
		return (NULL);
	ft_memcpy(str, buff, (r + 1));
	return (str);
}

static char	*cut_buff(char *buff)
{
	ssize_t	r;
	ssize_t	i;
	char	*str2;

	r = check_next_line(buff);
	if (r == -1)
		return (buff);
	i = ft_strlen(&buff[r + 1]);
	if (i == 0)
	{
		free(buff);
		return (NULL);
	}
	str2 = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!str2)
		return (NULL);
	ft_memcpy(str2, &buff[r + 1], i);
	free (buff);
	buff = (char *)ft_calloc (sizeof(char), (i + 1));
	ft_memcpy(buff, str2, i);
	free (str2);
	return (buff);
}

static char	*read_file(char *buff, char *str, ssize_t check, int fd)
{
	char	*tmp;
	ssize_t	r;

	while (check > 0)
	{
		if (!buff)
		{
			buff = (char *)ft_calloc(sizeof(char), (ft_strlen(str) + 1));
			if (!buff)
				return (NULL);
			ft_memcpy(buff, str, ft_strlen(str));
		}
		else
		{
			tmp = ft_strjoin(buff, str);
			free(buff);
			buff = tmp;
		}
		r = check_next_line(buff);
		if (r >= 0)
			break ;
		ft_bzero(str, BUFFER_SIZE);
		check = read(fd, str, BUFFER_SIZE);
	}
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*str;
	ssize_t		check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	check = read(fd, str, BUFFER_SIZE);
	buff = read_file(buff, str, check, fd);
	free (str);
	str = cut_str(buff);
	buff = cut_buff(buff);
	if (str == NULL && buff)
	{
		str = (char *)ft_calloc(sizeof(char), ((ft_strlen(buff)) + 1));
		if (!str)
			return (NULL);
		ft_memcpy(str, buff, (ft_strlen(buff)));
		free (buff);
		buff = NULL;
	}
	return (str);
}

// int	main()
// {
// 	int 	fd;
// 	char 	*fichero;
// 	fd = open("fichero2.txt", O_RDONLY);
// 	fichero = get_next_line(fd);
// 	printf("%s", fichero);
// 	free(fichero);
// 	fichero = get_next_line(fd);
// 	printf("%s", fichero);
// 	// while (fichero != NULL)
// 	// {
// 	// 	printf("%s", fichero);
// 	// 	free(fichero);
// 	// 	fichero = get_next_line(fd);
// 	// }
// 	close(fd);
// 	free(fichero);
// 	system("leaks a.out");
// 	return (0);
// }