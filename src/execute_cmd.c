/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/02/10 16:04:31 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	exec_cmd_line_rec(const t_list *cmd_list, int fd_in, int fd_out)
{
	int	pipe_fds[2];

	if (cmd_list->next != NULL)
	{
		if (pipe(pipe_fds) != 0)
			return (FAILURE);
		exec_cmd_line_rec(cmd_list->next, pipe_fds[0], fd_out);
		cmd_list->cmd->pid = exec_single_cmd(*cmd_list->cmd, fd_in, pipe_fds[1],
				pipe_fds[0]);
	}
	else
		cmd_list->cmd->pid = exec_single_cmd(*cmd_list->cmd, fd_in, fd_out, 0);
	return (SUCCESS);
}

int	exec_cmd_line(t_list *cmd_list, int fd_in, int fd_out)
{
	t_list	*tmp;

	if (exec_cmd_line_rec(cmd_list, fd_in, fd_out) != SUCCESS)
		return (FAILURE);
	print_list(cmd_list);
	tmp = cmd_list;
	while (tmp != NULL)
	{
		printf("waiting for pid: %d\n", tmp->cmd->pid);
		waitpid(tmp->cmd->pid, NULL, 0);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	exec_single_cmd(const t_cmd exec, int fd_in, int fd_out, int to_close)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (pid);
	if (pid == 0)
	{
		printf("executing %s, fd_in:%d, fd_out:%d \n", exec.bin, fd_in, fd_out);
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
		close(to_close);
		if (access(exec.bin, X_OK) == 0)
			execve(exec.bin, exec.args, exec.envp);
		perror(exec.bin);
		return (FAILURE);
	}
	close(fd_in);
	close(fd_out);
	return (pid);
}
