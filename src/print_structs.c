/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:12:46 by hrother           #+#    #+#             */
/*   Updated: 2024/03/10 20:53:52 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void	print_cmd(void *command)
{
	t_cmd		*cmd;
	int			i;
	t_log_level	level;

	level = INFO;
	cmd = (t_cmd *)command;
	log_msg(level, "cmd: %s", cmd->bin);
	log_msg(level, "pid: %d", cmd->pid);
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
	log_msg(INFO, "type: %i value: %s", tkn->type, tkn->value);
}

void	print_token_new(void *p_tkn)
{
	t_token	*token;

	token = ((t_token *)p_tkn);
	char *names[] = {
		"NOTDEF		",
		"CMD		",
		"ARG		",
		"R_IN		",
		"R_OUT		",
		"R_APPEND	",
		"R_HEREDOC	",
		"PIPE		",
	};
	if (token->type < 0 || token->type > 7)
		log_msg(WARNING, "type = %i: Type out of range!\n", token->type);
	log_msg(DEBUG, "%i:%s [%s]", token->type, names[token->type], token->value);
}

void	print_list(t_list *lst)
{
	while (lst != NULL)
	{
		print_cmd((t_cmd *)lst->content);
		lst = lst->next;
	}
}