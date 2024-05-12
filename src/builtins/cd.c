/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:37:52 by hrother           #+#    #+#             */
/*   Updated: 2024/05/12 17:07:47 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_cd(const t_cmd *cmd, t_list **envp)
{
	char	*old_cwd;
	char	*new_cwd;

	if (!cmd->args || !cmd->args[0] || !cmd->args[1] || cmd->args[2])
	{
		log_msg(ERROR, "cd: wrong usage");
		return (EXIT_FAILURE);
	}
	old_cwd = getcwd(NULL, 0);
	if (!old_cwd)
		return (log_msg(ERROR, "cd: %s", strerror(errno)), EXIT_FAILURE);
	if (chdir(cmd->args[1]) != EXIT_SUCCESS)
		return (log_msg(ERROR, "cd: %s", strerror(errno)), free(old_cwd),
			EXIT_FAILURE);
	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
		return (log_msg(ERROR, "cd: %s", strerror(errno)), free(old_cwd),
			EXIT_FAILURE);
	export_env_var(envp, "PWD", new_cwd);
	export_env_var(envp, "OLDPWD", old_cwd);
	return (EXIT_SUCCESS);
}
