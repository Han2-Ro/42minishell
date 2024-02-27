/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/02/27 23:00:38 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	exec(const t_cmd cmd)
{
	log_msg(INFO, "executing %s", cmd.bin);
	if (access(cmd.bin, X_OK) == 0)
		execve(cmd.bin, cmd.args, cmd.envp);
	perror(cmd.bin);
	return (FAILURE);
}

int	setup_pipe(void)
{
	int	pipe_fds[2];
	int	pid;

	if (pipe(pipe_fds) != 0)
		return (FAILURE);
	log_msg(DEBUG, "pipe_fds[0]: %d, pipe_fds[1]: %d", pipe_fds[0],
		pipe_fds[1]);
	pid = fork();
	if (pid < 0)
		return (FAILURE);
	if (pid == 0)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	else
	{
		close(pipe_fds[1]);
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
	}
	return (pid);
}

int	wait_pids(t_list *cmd_list)
{
	t_list	*tmp;

	tmp = cmd_list;
	while (tmp != NULL)
	{
		log_msg(DEBUG, "waiting for pid: %d", tmp->cmd->pid);
		waitpid(tmp->cmd->pid, NULL, 0);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	setup_io(int fd_in, int fd_out)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (FAILURE);
	if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		return (pid);
	}
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
	return (pid);
}

int	exec_cmd_line(t_list *cmd_list, int fd_in, int fd_out)
{
	t_list	*tmp;

	log_msg(DEBUG, "fd_in: %d, fd_out: %d", fd_in, fd_out);
	if (setup_io(fd_in, fd_out) > 0)
		return (SUCCESS);
	tmp = cmd_list;
	while (tmp != NULL && tmp->next != NULL)
	{
		tmp->cmd->pid = setup_pipe();
		if (tmp->cmd->pid < 0)
			return (FAILURE);
		if (tmp->cmd->pid == 0)
			exec(*tmp->cmd);
		tmp = tmp->next;
	}
	tmp->cmd->pid = fork();
	if (tmp->cmd->pid < 0)
		return (FAILURE);
	if (tmp->cmd->pid == 0)
		exec(*tmp->cmd);
	wait_pids(cmd_list);
	exit(0);
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
		log_msg(DEBUG, "executing %s, fd_in:%d, fd_out:%d", exec.bin, fd_in,
			fd_out);
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
