/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:05:28 by hrother           #+#    #+#             */
/*   Updated: 2024/03/13 17:53:45 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(const char *filename, int flags, int *fd)
{
	if (*fd > 2)
		close(*fd);
	*fd = open(filename, flags, 0644);
	if (*fd < 0)
		return (log_msg(ERROR, "%s: %s", filename, strerror(errno)), FAILURE);
	return (SUCCESS);
}

int	redir_to_fd(const t_token *token, t_cmd *cmd)
{
	if (token->type == R_IN)
		open_file(token->value, O_RDONLY, &cmd->fd_in);
	else if (token->type == R_HEREDOC)
		here_doc(token->value, &cmd->fd_in);
	else if (token->type == R_OUT)
		open_file(token->value, O_WRONLY | O_CREAT | O_TRUNC, &cmd->fd_out);
	else if (token->type == R_APPEND)
		open_file(token->value, O_WRONLY | O_CREAT | O_APPEND, &cmd->fd_out);
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	redirs_to_fds(t_list *cmd_list)
{
	t_list	*current_cmd;
	t_list	*current_tkn;
	t_cmd	*cmd;

	current_cmd = cmd_list;
	while (current_cmd != NULL)
	{
		cmd = (t_cmd *)current_cmd->content;
		current_tkn = cmd->redirects;
		while (current_tkn != NULL)
		{
			if (redir_to_fd((t_token *)current_tkn->content, cmd) == FAILURE)
			{
				break ;
			}
			current_tkn = current_tkn->next;
		}
		current_cmd = current_cmd->next;
	}
	return (SUCCESS);
}
