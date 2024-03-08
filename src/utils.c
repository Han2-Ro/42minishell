/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:41:35 by hrother           #+#    #+#             */
/*   Updated: 2024/03/07 16:25:15 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*new_cmd(char *bin, char **args, char **envp)
{
	t_cmd	*cmd;

	// TODO: maybe we don't even need to malloc this
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (log_msg(ERROR, "malloc failed"), NULL);
	cmd->bin = bin;
	cmd->args = args;
	cmd->envp = envp;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->pid = -1;
	return (cmd);
}

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	free(cmd->bin);
	free_nullterm_str_arr(cmd->args);
	ft_lstclear(&cmd->in, free_redir);
	ft_lstclear(&cmd->out, free_redir);
	free(cmd);
}

t_redirect	*new_redir(char *filename)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	redirect->filename = filename;
	return (redirect);
}

void	free_redir(void *content)
{
	t_redirect	*redir;

	redir = (t_redirect *)content;
	free(redir->filename);
	free(redir);
}

void	free_str_arr(char **strs, int size)
{
	while (size < 0)
	{
		free(strs[size - 1]);
		size--;
	}
	free(strs);
}

void	free_nullterm_str_arr(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}