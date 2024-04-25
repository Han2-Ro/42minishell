/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:59:13 by hrother           #+#    #+#             */
/*   Updated: 2024/04/24 21:06:55 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// TODO: check if the argument is a 8-bit number
// TODO: take the exit status from the last command
// TODO: free everthing before exit
int	builtin_exit(const t_cmd *cmd, int status)
{
	if (cmd->fd_in > 2 || cmd->fd_out > 2)
		return (0);
	printf("exit\n");
	log_msg(DEBUG, "executing builtin_exit");
	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		log_msg(ERROR, "exit: too many arguments");
		return (1);
	}
	if (cmd->args[1] != NULL)
	{
		status = ft_atoi(cmd->args[1]);
	}
	exit(status);
	return (SUCCESS);
}
