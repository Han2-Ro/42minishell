/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buitin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:36:34 by hrother           #+#    #+#             */
/*   Updated: 2024/05/29 11:50:36 by aprevrha         ###   ########.fr       */
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

int	exec_builtin(t_cmd *cmd, t_evars *evars)
{
	if (ft_strncmp(cmd->args[0], "pwd", 5) == 0)
		return (builtin_pwd(cmd));
	if (ft_strncmp(cmd->args[0], "cd", 5) == 0)
		return (builtin_cd(cmd, &evars->envl));
	if (ft_strncmp(cmd->args[0], "env", 5) == 0)
		return (builtin_env(cmd, &evars->envl));
	if (ft_strncmp(cmd->args[0], "export", 10) == 0)
		return (builtin_export(cmd, &evars->envl));
	if (ft_strncmp(cmd->args[0], "exit", 10) == 0)
		return (builtin_exit(cmd, evars));
	if (ft_strncmp(cmd->args[0], "echo", 10) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->args[0], "unset", 10) == 0)
		return (builtin_unset(cmd, &evars->envl));
	return (FAILURE);
}
