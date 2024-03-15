/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:19 by hrother           #+#    #+#             */
/*   Updated: 2024/03/13 18:08:12 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_until_delimiter(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (FAILURE);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			return (SUCCESS);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	here_doc(const char *delimiter, int *fd)
{
	int	pipe_fds[2];

	if (*fd > 2)
		close(*fd);
	if (pipe(pipe_fds) < 0)
		return (log_msg(ERROR, "pipe: %s", strerror(errno)), FAILURE);
	*fd = pipe_fds[0];
	read_until_delimiter(pipe_fds[1], delimiter);
	close(pipe_fds[1]);
	return (SUCCESS);
}
