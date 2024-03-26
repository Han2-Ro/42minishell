/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:59:13 by hrother           #+#    #+#             */
/*   Updated: 2024/03/25 18:16:07 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_exit(const t_cmd *cmd, t_list **envp)
{
	int exit_status;

	(void)envp;
	exit_status = 0;
	printf("exit\n");
	log_msg(DEBUG, "executing builtin_exit");
	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		log_msg(ERROR, "exit: too many arguments");
		return (FAILURE);
	}
	// TODO: take the exit status from the last command
	if (cmd->args[1] != NULL)
	{
		// TODO: check if the argument is a number
		exit_status = ft_atoi(cmd->args[1]);
	}
	// TODO: free everthing before exit
	exit(exit_status);
	return (SUCCESS);
}