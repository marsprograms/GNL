/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariade- <mariade-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:09:02 by mariade-          #+#    #+#             */
/*   Updated: 2026/06/05 19:09:02 by mariade-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*leftover = NULL;
	char			buffer[BUFFER_SIZE + 1];
	char			*line;
	ssize_t			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer[0], 0) < 0)
		return (NULL);
	bytes_read = 1;
	while (!gnl_strchr(leftover, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		leftover = gnl_strjoin(leftover, buffer);
		if (!leftover)
			return (NULL);
	}
	if (bytes_read == -1 || !leftover || *leftover == '\0')
		return (free(leftover), leftover = NULL, NULL);
	line = extract_line(leftover);
	leftover = update_stash(leftover, 0, 0);
	return (line);
}
/* #include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
} */