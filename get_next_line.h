/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariade- <mariade-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:12:19 by mariade-          #+#    #+#             */
/*   Updated: 2026/06/18 17:16:16 by mariade-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>


char	*get_next_line(int fd);
ssize_t	gnl_strlen(char *line);
char	*find_new_line(char *line, int c);
char	*gnl_strjoin(char *s1, char *s2);
char	*extract_line(char *line);
char	*update_stash(char *line, ssize_t start, ssize_t len);

#endif