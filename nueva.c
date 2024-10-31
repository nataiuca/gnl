#include "get_next_line.h"

static void handle_read_error(char **remainder)
{
    free(*remainder);
    *remainder = NULL;
}

static char *append_buffer(char *remainder, char *buf)
{
    char    *temp;

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

static int read_and_store(int fd, char **remainder)
{
    char    buf[BUFFER_SIZE + 1];
    int     read_bytes;

    read_bytes = read(fd, buf, BUFFER_SIZE);
    while (read_bytes > 0)
    {
        buf[read_bytes] = '\0';
        *remainder = append_buffer(*remainder, buf);
        if (!*remainder)
            return (-1);
        if (ft_strchr(*remainder, '\n'))
            break ;
        read_bytes = read(fd, buf, BUFFER_SIZE);
    }
    return (read_bytes);
}

static char *get_line(char **remainder)
{
    char    *temp;
    char    *line;
    size_t  len;

    if (!(*remainder))
        return (NULL);
    temp = ft_strchr(*remainder, '\n');
    if (temp)
    {
        len = temp - *remainder + 1;
        line = ft_strndup(*remainder, len);
        if (!line)
            return (NULL);
        char *new_remainder = ft_strdup(temp + 1);
        if (!new_remainder)
        {
            free(line);
            return (NULL);
        }
        free(*remainder);
        *remainder = new_remainder;
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

char *get_next_line(int fd)
{
    static char *remainder;
    int         read_bytes;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    read_bytes = read_and_store(fd, &remainder);
    if (read_bytes == -1)
    {
        handle_read_error(&remainder);
        return (NULL);
    }
    if (read_bytes == 0 && !remainder)
        return (NULL);
    return (get_line(&remainder));
}
