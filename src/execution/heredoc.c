/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:53:19 by hrother           #+#    #+#             */
/*   Updated: 2024/04/30 19:22:11 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_until_delimiter(int fd, const t_token *token, t_evars *evars)
{
	char	*line;

	while (1)
	{
		line = ft_readline("> ", evars->tty);
		if (line == NULL)
			return (FAILURE);
		if (ft_strcmp(line, token->value) == 0)
		{
			free(line);
			return (SUCCESS);
		}
		if (token->type == R_HEREDOC)
			expand_heredoc(&line, evars->envp, evars->status);
		if (line == NULL)
			return (FAILURE);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	here_doc(const t_token *token, int *fd, t_evars *evars)
{
	int	pipe_fds[2];

	if (*fd > 2)
		close(*fd);
	if (pipe(pipe_fds) < 0)
		return (log_msg(ERROR, "pipe: %s", strerror(errno)), FAILURE);
	*fd = pipe_fds[0];
	read_until_delimiter(pipe_fds[1], token, evars);
	close(pipe_fds[1]);
	return (SUCCESS);
}
