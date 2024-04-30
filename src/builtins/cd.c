/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:37:52 by hrother           #+#    #+#             */
/*   Updated: 2024/04/30 18:03:22 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// consider updating the PWD env var
int	builtin_cd(const t_cmd *cmd, t_list **envp)
{
	(void)envp;
	if (!cmd->args || !cmd->args[0] || !cmd->args[1] || cmd->args[2])
	{
		log_msg(ERROR, "cd: wrong usage");
		return (EXIT_FAILURE);
	}
	if (chdir(cmd->args[1]) != EXIT_SUCCESS)
	{
		log_msg(ERROR, "cd: %s", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
