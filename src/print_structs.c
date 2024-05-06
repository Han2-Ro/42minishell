/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:12:46 by hrother           #+#    #+#             */
/*   Updated: 2024/05/06 21:01:55 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
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
	ft_lstiter(cmd->redirects, print_token);
}

void	print_token(void *token)
{
	t_token	*tkn;

	tkn = (t_token *)token;
	log_msg(DEBUG, "type: %i value: %s", tkn->type, tkn->value);
}

void	print_token_new(void *p_tkn)
{
	t_token	*token;
	char	*names[9];

	names[0] = "NOTDEF		";
	names[1] = "CMD			";
	names[2] = "ARG			";
	names[3] = "R_IN		";
	names[4] = "R_OUT		";
	names[5] = "R_APPEND	";
	names[6] = "R_HEREDOC	";
	names[7] = "PIPE		";
	names[8] = "R_QUOTEDOC	";
	token = ((t_token *)p_tkn);
	if (token->type < 0 || token->type > 8)
		log_msg(WARNING, "type = %i: Type out of range!\n", token->type);
	log_msg(DEBUG, "%i:%s [%s]", token->type, names[token->type], token->value);
}
