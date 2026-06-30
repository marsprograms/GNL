/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariade- <mariade-student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:12:27 by mariade-          #+#    #+#             */
/*   Updated: 2026/06/30 04:59:49 by mariade-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *line)
{
	size_t	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
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
			return (line);
		line++;
	}
	return (NULL);
}

char	*gnl_strjoin(char *line, char *buffer)
{
	char		*str;
	size_t		i;
	size_t		j;

	if (!buffer)
		return (NULL);
	str = malloc ((gnl_strlen(line) + gnl_strlen(buffer) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (line)
		while (line[i])
			str[j++] = line[i++];
	i = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(line);
	return (str);
}

char	*extract_line(char *line)
{
	char	*str;
	size_t	i;
	size_t	end;

	if (!line)
		return (free(line), NULL);
	end = 0;
	while (line[end] && line[end] != '\n')
		end++;
	if (line[end] == '\n')
		end++;
	str = malloc (end + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < end)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*update_stash(char *line, size_t start, size_t len)
{
	char	*new_stash;
	size_t	i;

	if (!line)
		return (free(line), NULL);
	while (line[start] && line[start] != '\n')
		start++;
	if (!line[start])
		return (free(line), NULL);
	start++;
	len = gnl_strlen(line + start);
	if (len == 0)
		return (free(line), NULL);
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (free(line), NULL);
	i = 0;
	while (i < len)
	{
		new_stash[i] = line[start + i];
		i++;
	}
	new_stash[i] = '\0';
	free(line);
	return (new_stash);
}
