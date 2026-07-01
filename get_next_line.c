/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariade- <mariade-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:12:16 by mariade-          #+#    #+#             */
/*   Updated: 2026/07/01 03:55:45 by mariade-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	size_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (!*buffer)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read < 0)
				return (free(line), NULL);
			buffer[bytes_read] = '\0';
			if (bytes_read == 0)
				return (line);
		}
		line = gnl_strjoin(line, buffer);
		update_buffer(buffer);
		if (find_new_line(line, '\n'))
			break ;
	}
	return (line);
}
