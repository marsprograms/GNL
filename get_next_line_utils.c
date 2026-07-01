/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariade- <mariade-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:12:27 by mariade-          #+#    #+#             */
/*   Updated: 2026/07/01 03:52:26 by mariade-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *line)
{
	size_t	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	return (i);
}

char	*find_new_line(char *line, int c)
{
	if (!line)
		return (NULL);
	while (*line)
	{
		if (*line == (unsigned char)c)
			return (line + 1);
		line++;
	}
	return (NULL);
}

char	*gnl_strjoin(char *line, char *buffer)
{
	char		*str;
	size_t		len_line;
	size_t		len_buffer;

	if (!buffer)
		return (line);
	len_line = gnl_strlen(line);
	len_buffer = gnl_strlen(buffer);
	str = malloc(sizeof(char) * (len_line + len_buffer + 1));
	if (!str)
		return (free(str), NULL);
	ft_memcpy(str, line, len_line);
	free(line);
	ft_memcpy(str + len_line, buffer, len_buffer);
	str[len_line + len_buffer] = '\0';
	return (str);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;
	size_t			i;

	dest_ptr = dest;
	src_ptr = src;
	i = 0;
	while (i < n)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}

void	update_buffer(char *buffer)
{
	char	*new_buffer;
	size_t	start;
	int		i;

	start = gnl_strlen(buffer);
	new_buffer = buffer + start;
	i = 0;
	if (!start)
		return ;
	while (new_buffer[i])
	{
		buffer[i] = new_buffer[i];
		i++;
	}
	buffer[i] = '\0';
}
