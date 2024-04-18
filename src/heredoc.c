/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:19 by hrother           #+#    #+#             */
/*   Updated: 2024/04/18 19:35:51 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_until_delimiter(int fd, const char *delimiter, t_list *env_list,
		int status)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		// TODO: extract this to a separate function (ft_readline)
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
		{
			line = get_next_line(STDIN_FILENO);
			if (line && line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
		}
		if (line == NULL)
			return (FAILURE);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			return (SUCCESS);
		}
		expanded_line = expand(line, env_list, status);
		if (expanded_line == NULL)
			return (free(line), FAILURE);
		ft_putendl_fd(expanded_line, fd);
		free(expanded_line);
		free(line);
	}
}

int	here_doc(const char *delimiter, int *fd, t_list *env_list, int status)
{
	int	pipe_fds[2];

	if (*fd > 2)
		close(*fd);
	if (pipe(pipe_fds) < 0)
		return (log_msg(ERROR, "pipe: %s", strerror(errno)), FAILURE);
	*fd = pipe_fds[0];
	read_until_delimiter(pipe_fds[1], delimiter, env_list, status);
	close(pipe_fds[1]);
	return (SUCCESS);
}
