/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:41:35 by hrother           #+#    #+#             */
/*   Updated: 2024/03/06 19:09:03 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*new_cmd(char *bin, char **args, char **envp)
{
	t_cmd	*cmd;

	// TODO: maybe we don't even need to malloc this
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->bin = bin;
	cmd->args = args;
	cmd->envp = envp;
	cmd->pid = -1;
	return (cmd);
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
