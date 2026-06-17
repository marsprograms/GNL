/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariade- <mariade-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:12:27 by mariade-          #+#    #+#             */
/*   Updated: 2026/06/17 14:44:14 by mariade-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	gnl_strlen(char *line)
{
	ssize_t	i;

	if (!line)
		return (0);
	i = 0;
	while(line[i])
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

char	*gnl_strjoin(char *s1, char *s2)
{
	char		*str;
	ssize_t		i;
	ssize_t		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc (gnl_strlen(s1) + gnl_strlen(s2) + 1 * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*extract_line(char *line)
{
	
}

char	*update_stash(char *line, ssize_t start, ssize_t end)
{
	
}
