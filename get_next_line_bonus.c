/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:43:02 by natferna          #+#    #+#             */
/*   Updated: 2024/10/30 17:22:04 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_strcat(char *dst, const char *src)
{
	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*get_line(char **remainder)
{
	char	*line;
	char	*newline_pos;
	char	*temp;
	size_t	len;

	if (!(*remainder) || **remainder == '\0')
		return (NULL);
	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		len = newline_pos - *remainder + 1;
		line = ft_strndup(*remainder, len);
		if (!line)
			return (NULL);
		temp = ft_strdup(newline_pos + 1);
		free(*remainder);
		*remainder = temp;
		if (!*remainder)
			return (NULL);
		return (line);
	}
	line = *remainder;
	*remainder = NULL;
	return (line);
}

char	*append_buffer(char *remainder, char *buf)
{
	char	*temp;

	if (!remainder)
		return (ft_strdup(buf));
	temp = ft_strjoin(remainder, buf);
	free(remainder);
	return (temp);
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
		if (!remainder[fd])
			return (NULL);
		if (ft_strchr(remainder[fd], '\n'))
			break ;
		read_bytes = read(fd, buf, BUFFER_SIZE);
	}
	if (read_bytes == -1 || (read_bytes == 0 && (!remainder[fd]
				|| remainder[fd][0] == '\0')))
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	return (get_line(&remainder[fd]));
}
