/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:05:28 by hrother           #+#    #+#             */
/*   Updated: 2024/03/10 20:41:50 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(const char *filename, int flags, int *fd)
{
	if (*fd > 3)
		close(*fd);
	*fd = open(filename, flags, 0644);
	if (*fd < 0)
		return (log_msg(ERROR, "%s: %s", filename, strerror(errno)), FAILURE);
	return (SUCCESS);
}

int	here_doc(const char *delimiter, int *fd)
{
	if (*fd > 3)
		close(*fd);
	*fd = -1;
	log_msg(ERROR, "here_doc not implemented yet");
	return (FAILURE);
}

int	set_fds(void *command)
{
	t_cmd	*cmd;
	t_list	*current;
	t_token	*token;

	cmd = (t_cmd *)command;
	current = cmd->redirects;
	while (current != NULL)
	{
		token = (t_token *)current->content;
		if (token->type == R_IN)
			open_file(token->value, O_RDONLY, &cmd->fd_in);
		else if (token->type == R_HEREDOC)
			cmd->fd_in = here_doc(token->value, &cmd->fd_in);
		else if (token->type == R_OUT)
			open_file(token->value, O_WRONLY | O_CREAT | O_TRUNC, &cmd->fd_out);
		else if (token->type == R_APPEND)
			open_file(token->value, O_WRONLY | O_CREAT | O_APPEND,
				&cmd->fd_out);
		if (cmd->fd_in < 0 || cmd->fd_out < 0)
			return (FAILURE);
		current = current->next;
	}
}
