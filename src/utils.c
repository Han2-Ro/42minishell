/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:41:35 by hrother           #+#    #+#             */
/*   Updated: 2024/03/08 18:52:48 by hrother          ###   ########.fr       */
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
	free(cmd->args);
	ft_lstclear(&cmd->in, free);
	ft_lstclear(&cmd->out, free);
	free(cmd);
}

t_redirect	*new_redir(char *filename)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (log_msg(ERROR, "malloc failed"), NULL);
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
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/**
 * @brief This function does nothing: Useful for ft_lsclear
 */
void	pass(void *content)
{
	(void)content;
}
