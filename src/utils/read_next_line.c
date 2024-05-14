/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:21:19 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 14:14:41 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_next_line(int fd)
{
	char	*line;
	char	*tmp;
	char	buffer[2];
	int		bytes_read;

	line = malloc(1 * sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	ft_bzero(buffer, 2);
	while (line)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read <= 0)
			break ;
		tmp = ft_strjoin(line, buffer);
		free(line);
		line = tmp;
		if (buffer[0] == '\n')
			break ;
	}
	if (line && ft_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}
