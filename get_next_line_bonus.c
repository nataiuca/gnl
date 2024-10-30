/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:15:57 by natferna          #+#    #+#             */
/*   Updated: 2024/10/30 23:25:01 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(char **remainder)
{
	char	*line;
	char	*temp;
	size_t	len;

	if (!(*remainder))
		return (NULL);
	temp = ft_strchr(*remainder, '\n');
	if (temp)
	{
		len = temp - *remainder + 1;
		line = ft_strndup(*remainder, len);
		temp = ft_strdup(temp + 1);
		free(*remainder);
		*remainder = temp;
		if (**remainder == '\0')
		{
			free(*remainder);
			*remainder = NULL;
		}
		return (line);
	}
	line = ft_strdup(*remainder);
	free(*remainder);
	*remainder = NULL;
	return (line);
}

static char	*append_buffer(char *remainder, char *buf)
{
	char	*temp;

	if (!remainder)
		remainder = ft_strdup(buf);
	else
	{
		temp = ft_strjoin(remainder, buf);
		free(remainder);
		remainder = temp;
	}
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[MAX_FD];
	char		buf[BUFFER_SIZE + 1];
	int			read_bytes;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = read(fd, buf, BUFFER_SIZE);
	while (read_bytes > 0)
	{
		buf[read_bytes] = '\0';
		remainder[fd] = append_buffer(remainder[fd], buf);
		if (ft_strchr(remainder[fd], '\n'))
			break ;
		read_bytes = read(fd, buf, BUFFER_SIZE);
	}
	if (read_bytes == -1)
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	if (read_bytes == 0 && !remainder[fd])
		return (NULL);
	return (get_line(&remainder[fd]));
}
