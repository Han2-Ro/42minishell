/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buitin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:36:34 by hrother           #+#    #+#             */
/*   Updated: 2024/04/14 13:48:15 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(const t_cmd *cmd)
{
	if (ft_strncmp(cmd->bin, "pwd", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->bin, "cd", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->bin, "env", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->bin, "export", 10) == 0)
		return (true);
	if (ft_strncmp(cmd->bin, "exit", 10) == 0)
		return (true);
	if (ft_strncmp(cmd->bin, "echo", 10) == 0)
		return (true);
	if (ft_strncmp(cmd->bin, "unset", 10) == 0)
		return (true);
	return (false);
}

int	exec_builtin(t_cmd *cmd, t_list **envp)
{
	cmd->pid = 0;
	if (ft_strncmp(cmd->bin, "pwd", 5) == 0)
		return (builtin_pwd(cmd, envp));
	if (ft_strncmp(cmd->bin, "cd", 5) == 0)
		return (builtin_cd(cmd, envp));
	if (ft_strncmp(cmd->bin, "env", 5) == 0)
		return (builtin_env(cmd, envp));
	if (ft_strncmp(cmd->bin, "export", 10) == 0)
		return (builtin_export(cmd, envp));
	if (ft_strncmp(cmd->bin, "exit", 10) == 0)
		return (builtin_exit(cmd, envp));
	if (ft_strncmp(cmd->bin, "echo", 10) == 0)
		return (builtin_echo(cmd, envp));
	if (ft_strncmp(cmd->bin, "unset", 10) == 0)
		return (builtin_unset(cmd, envp));
	return (FAILURE);
}
