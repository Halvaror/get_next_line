/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-b <alopez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 21:14:21 by alopez-b          #+#    #+#             */
/*   Updated: 2021/10/16 16:19:56 by alopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_buff(char *buff, char *str, int fd)
{
	long long	i;
	char 		*str2;

	i = ft_strlen(buff);
	str = calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	str2 = calloc(sizeof(char), i + 1);
	if (!str2)
		return (NULL);
	read(fd, str, BUFFER_SIZE);
	ft_memcpy(str2, buff, i);
	free(buff);
	buff = calloc(sizeof(char), (i + BUFFER_SIZE) + 1);
	if (!buff)
		return (NULL);
	ft_memcpy(buff,str2,i);
	free(str2);
	buff = ft_strjoin(buff, str);
	free (str);
	return(buff);
}

static ssize_t	check_next_line(char *buff)
{
	ssize_t	i;

	i = 0;
	while(buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
static char	*cut_buff(char *buff, ssize_t check)
{
	ssize_t	i;
	char	*str2;

	i = ft_strlen(&buff[check + 1]);
	str2 = calloc(sizeof(char), (i + 1));
	if (!str2)
		return (NULL);
	ft_memcpy(str2, &buff[check + 1], i);
	free (buff);
	buff = calloc (sizeof(char), (i + 1));
	ft_memcpy(buff, str2, i);
	free (str2);
	return (buff);
}
static char	*cut_str(char *buff, char *str, ssize_t check)
{
	str = calloc(sizeof(char),(check + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, buff, check);
	return (str);
}

char	*get_next_line(int fd)
{
	static char			*buff;
	static char			*str;
	static ssize_t		check;
	
	if(!buff && check == 0)
		return(str);
	if (!buff)
	{
		buff = calloc(sizeof(char), BUFFER_SIZE + 1);
				if (!buff)
					return (NULL);
		check = read(fd, buff, BUFFER_SIZE);
		str = get_next_line(fd);
	}
	else
	{
		check = check_next_line(buff);
		if (check >= 0)
		{
			str = cut_str(buff, str,  check);
			buff = cut_buff(buff, check);
		}		
		else
		{
			buff = join_buff(buff, str, fd);
			str = get_next_line(fd);
		}
	}
	if(check == 0)
		if((check = check_next_line(buff)) == -1)
		{
			str = cut_str(buff, str, (ft_strlen(buff)));
			free (buff);
		}
	
	return (str);
}

int	main()
{
	int 	fd;
	char 	*fichero;
	
	fd = open("/Users/alopez-b/Documents/Cursus/get_next_line/fichero.txt", O_RDONLY);
	printf("frase: %s\n", fichero = get_next_line(fd));
	while (fichero != 0)
	{
		free (fichero);
		fichero = get_next_line(fd);
		printf("frase: %s\n", fichero);
	}
	close(fd);
	free(fichero);
	//system("leaks a.out");
	return (0);
}

