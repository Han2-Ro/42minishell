/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:37:52 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 22:11:53 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd_oldpwd(t_list **envp, char *new_cwd, char *old_cwd)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strdup("PWD");
	if (!pwd)
	{
		free(new_cwd);
		free(old_cwd);
		return ;
	}
	oldpwd = ft_strdup("OLDPWD");
	if (!oldpwd)
	{
		free(new_cwd);
		free(old_cwd);
		free(pwd);
		return ;
	}
	export_env_var(envp, pwd, new_cwd);
	export_env_var(envp, oldpwd, old_cwd);
}

int	builtin_cd(const t_cmd *cmd, t_list **envp)
{
	char	*old_cwd;
	char	*new_cwd;

	if (!cmd->args || !cmd->args[0] || !cmd->args[1] || cmd->args[2])
	{
		log_msg(ERROR, "cd: " MSG_WRONG_ARGC);
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
	update_pwd_oldpwd(envp, new_cwd, old_cwd);
	return (EXIT_SUCCESS);
}
