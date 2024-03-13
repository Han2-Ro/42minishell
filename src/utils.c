/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:41:35 by hrother           #+#    #+#             */
/*   Updated: 2024/03/13 17:15:13 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*new_cmd(char *bin, char **args, char **envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (log_msg(ERROR, "malloc failed"), NULL);
	cmd->bin = bin;
	cmd->args = args;
	cmd->envp = envp;
	cmd->redirects = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->pid = -1;
	return (cmd);
}

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	free(cmd->args);
	ft_lstclear(&cmd->redirects, pass);
	free(cmd);
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
