/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:12:46 by hrother           #+#    #+#             */
/*   Updated: 2024/06/09 11:07:20 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_cmd(void *command)
{
	t_cmd		*cmd;
	int			i;
	t_log_level	level;

	level = DEBUG;
	cmd = (t_cmd *)command;
	log_msg(level, "cmd: %s", cmd->bin);
	log_msg(level, "pid: %d", cmd->pid);
	log_msg(level, "status: %i", cmd->status);
	log_msg(level, "args:");
	i = 0;
	while (cmd->args[i] != NULL)
	{
		log_msg(level, "  %s", cmd->args[i]);
		i++;
	}
	log_msg(level, "fd_in: %d, fd_out: %d", cmd->fd_in, cmd->fd_out);
	ft_lstiter(cmd->redirects, print_token_new);
}

void	print_token_new(void *p_tkn)
{
	t_token	*token;
	char	*names[9];

	names[0] = "NOTDEF		";
	names[1] = "ARG			";
	names[2] = "R_IN		";
	names[3] = "R_OUT		";
	names[4] = "R_APPEND	";
	names[5] = "R_HEREDOC	";
	names[6] = "PIPE		";
	names[7] = "R_QUOTEDOC	";
	token = ((t_token *)p_tkn);
	if (token->type < 0 || token->type > 7)
		log_msg(WARNING, "type = %i: Type out of range!\n", token->type);
	log_msg(DEBUG, "%i:%s [%s]", token->type, names[token->type], token->value);
}
