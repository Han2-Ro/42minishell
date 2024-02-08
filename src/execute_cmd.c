/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/02/08 15:38:32 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	exec_cmd_line(const t_list *cmd_list, int fd_in, int fd_out)
{
	t_list	*current;
	int		pipe_fds[2];

	current = cmd_list;
	if (current->next != NULL)
	{
		if (pipe(pipe_fds) != 0)
			return (FAILURE);
		exec_cmd_line(current->next, pipe_fds[0], fd_out);
	}
	exec_single_cmd(*current->cmd, fd_in, pipe_fds[1]);
}

int	exec_single_cmd(const t_cmd exec, int fd_in, int fd_out)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (pid);
	if (pid == 0)
	{
		if (fd_in != STDIN_FILENO)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != STDOUT_FILENO)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		if (access(exec.bin, X_OK) == 0)
			execve(exec.bin, exec.args, exec.envp);
		perror(exec.bin);
		return (-1);
	}
	return (pid);
}
