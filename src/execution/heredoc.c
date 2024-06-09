/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:19 by hrother           #+#    #+#             */
/*   Updated: 2024/05/30 18:58:41 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_until_delimiter(int fd, const t_token *token, t_evars *evars)
{
	char	*line;

	while (1)
	{
		line = ft_readline("> ", evars->tty);
		if (g_signal == SIGINT)
			return (free(line), evars->status = 128 + g_signal, g_signal = 0,
				FAILURE);
		if (line == NULL)
		{
			log_msg(ERROR, MSG_EOF, token->value);
			return (SUCCESS);
		}
		if (ft_strcmp(line, token->value) == 0)
		{
			free(line);
			return (SUCCESS);
		}
		if (token->type == R_HEREDOC)
			expand_heredoc(&line, *evars);
		if (line == NULL)
			return (FAILURE);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	here_doc(const t_token *token, int *fd, t_evars *evars)
{
	int	pipe_fds[2];
	int	ret;

	if (*fd > 2)
		close(*fd);
	if (pipe(pipe_fds) < 0)
		return (log_msg(ERROR, "pipe: %s", strerror(errno)), FAILURE);
	*fd = pipe_fds[0];
	ret = read_until_delimiter(pipe_fds[1], token, evars);
	close(pipe_fds[1]);
	return (ret);
}
