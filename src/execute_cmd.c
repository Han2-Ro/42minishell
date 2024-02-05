/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/02/05 17:22:39 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	exec_cmd(const t_exec exec)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (pid);
	if (pid == 0)
	{
		if (exec.fd_in != STDIN_FILENO)
		{
			dup2(exec.fd_in, STDIN_FILENO);
			close(exec.fd_in);
		}
		if (exec.fd_out != STDOUT_FILENO)
		{
			dup2(exec.fd_out, STDOUT_FILENO);
			close(exec.fd_out);
		}
		if (access(exec.bin, X_OK) == 0)
			execve(exec.bin, exec.args, exec.envp);
		perror(exec.bin);
		return (-1);
	}
	return (pid);
}
