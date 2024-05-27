/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buitin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:36:34 by hrother           #+#    #+#             */
/*   Updated: 2024/05/27 17:03:32 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(const t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "pwd", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->args[0], "cd", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->args[0], "env", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->args[0], "export", 10) == 0)
		return (true);
	if (ft_strncmp(cmd->args[0], "exit", 10) == 0)
		return (true);
	if (ft_strncmp(cmd->args[0], "echo", 10) == 0)
		return (true);
	if (ft_strncmp(cmd->args[0], "unset", 10) == 0)
		return (true);
	return (false);
}

int	exec_builtin(t_cmd *cmd, t_list **envp, int status)
{
	if (ft_strncmp(cmd->args[0], "pwd", 5) == 0)
		return (builtin_pwd(cmd, envp));
	if (ft_strncmp(cmd->args[0], "cd", 5) == 0)
		return (builtin_cd(cmd, envp));
	if (ft_strncmp(cmd->args[0], "env", 5) == 0)
		return (builtin_env(cmd, envp));
	if (ft_strncmp(cmd->args[0], "export", 10) == 0)
		return (builtin_export(cmd, envp));
	if (ft_strncmp(cmd->args[0], "exit", 10) == 0)
		return (builtin_exit(cmd, status));
	if (ft_strncmp(cmd->args[0], "echo", 10) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->args[0], "unset", 10) == 0)
		return (builtin_unset(cmd, envp));
	return (FAILURE);
}
