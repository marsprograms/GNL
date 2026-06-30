/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariade- <mariade-student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:12:16 by mariade-          #+#    #+#             */
/*   Updated: 2026/06/30 04:35:21 by mariade-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), stash = NULL, NULL);
	bytes_read = 1;
	while (!find_new_line(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = gnl_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	if (bytes_read == -1 || !stash || *stash == '\0')
		return (free(stash), stash = NULL, NULL);
	line = extract_line(stash);
	stash = update_stash(stash, 0, 0);
	return (line);
}
