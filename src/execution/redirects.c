/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:05:28 by hrother           #+#    #+#             */
/*   Updated: 2024/05/27 17:05:20 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	open_file(const char *filename, int flags, int *fd)
{
	if (*fd > 2)
		close(*fd);
	*fd = open(filename, flags, 0644);
	if (*fd < 0)
		return (log_msg(ERROR, "%s: %s", filename, strerror(errno)), FAILURE);
	return (SUCCESS);
}

int	redir_to_fd(const t_token *token, t_cmd *cmd, t_evars *evars, int fd)
{
	if (token->type == R_IN && fd == STDIN_FILENO)
		open_file(token->value, O_RDONLY, &cmd->fd_in);
	else if ((token->type == R_HEREDOC || token->type == R_QUOTEDOC)
		&& fd == STDIN_FILENO)
	{
		if (here_doc(token, &cmd->fd_in, evars) != SUCCESS)
			return (HEREDOC_CANCLED);
	}
	else if (token->type == R_OUT && fd == STDOUT_FILENO)
		open_file(token->value, O_WRONLY | O_CREAT | O_TRUNC, &cmd->fd_out);
	else if (token->type == R_APPEND && fd == STDOUT_FILENO)
		open_file(token->value, O_WRONLY | O_CREAT | O_APPEND, &cmd->fd_out);
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (INVALID_FILE);
	return (SUCCESS);
}

int	redirs_to_fds(t_list *cmd_list, t_evars *evars, int fd)
{
	t_list	*current_tkn;
	t_cmd	*cmd;
	int		redir_status;

	while (cmd_list != NULL)
	{
		cmd = (t_cmd *)(cmd_list->content);
		current_tkn = cmd->redirects;
		while (current_tkn != NULL)
		{
			redir_status = redir_to_fd((t_token *)current_tkn->content, cmd,
					evars, fd);
			if (redir_status == INVALID_FILE)
			{
				cmd->status = 1;
				break ;
			}
			if (redir_status == HEREDOC_CANCLED)
				return (HEREDOC_CANCLED);
			current_tkn = current_tkn->next;
		}
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}
