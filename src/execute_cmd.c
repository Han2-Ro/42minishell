/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/02/08 15:23:45 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	exec_cmd_line(const t_pipe pipe_node, int fd_in, int fd_out)
{
	int	pipe_fds[2];
	int	pids[2];

	if (pipe(pipe_fds) < 0)
		return (-1);
	pids[0] = exec_node(pipe_node.child1, fd_in, pipe_fds[1]);
	pids[1] = exec_node(pipe_node.child2, pipe_fds[0], fd_out);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
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
