/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorfanu <lorfanu@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:52:55 by lorfanu           #+#    #+#             */
/*   Updated: 2022/05/16 02:49:12 by lorfanu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** A function that returns a line read from a file descriptor & returns: 
** Read line: correct behavior (reading one line at a time)
** NULL: there is nothing else to read, or an error occurred
*/

#include "get_next_line.h"

static char	*ft_read_and_save(int fd, char *saved_bytes)
{
	char	*buff;
	int		read_value;

	read_value = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!ft_strchr(saved_bytes, '\n') && read_value != 0)
	{
		read_value = read(fd, buff, BUFFER_SIZE);
		if (read_value == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_value] = '\0';
		saved_bytes = ft_strjoin(saved_bytes, buff);
	}
	free(buff);
	return (saved_bytes);
}

static char	*ft_get_line(char *saved_bytes)
{
	int		i;
	char	*s;

	i = 0;
	if (!saved_bytes[i])
		return (NULL);
	while (saved_bytes[i] && saved_bytes[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (saved_bytes[i] && saved_bytes[i] != '\n')
	{
		s[i] = saved_bytes[i];
		i++;
	}
	if (saved_bytes[i] == '\n')
	{
		s[i] = saved_bytes[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

static char	*ft_update_saved_bytes(char *saved_bytes)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (saved_bytes[i] != '\0' && saved_bytes[i] != '\n')
		i++;
	if (!saved_bytes[i])
	{
		free(saved_bytes);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(saved_bytes) - i + 1));
	if (!s)
		return (NULL);
	i = i + 1;
	while (saved_bytes[i])
		s[j++] = saved_bytes[i++];
	s[j] = '\0';
	free(saved_bytes);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	saved_bytes = ft_read_and_save(fd, saved_bytes);
	if (!saved_bytes)
		return (NULL);
	line = ft_get_line(saved_bytes);
	saved_bytes = ft_update_saved_bytes(saved_bytes);
	return (line);
}
