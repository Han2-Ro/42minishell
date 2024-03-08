/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/03/06 18:51:41 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	exec(t_cmd cmd)
{
	exec_builtin(cmd);
	cmd.bin = path_to_bin(cmd.bin);
	log_msg(INFO, "executing %s", cmd.bin);
	if (access(cmd.bin, X_OK) == 0)
		execve(cmd.bin, cmd.args, __environ);
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
		log_msg(DEBUG, "waiting for pid: %d", ((t_cmd *)tmp->content)->pid);
		waitpid(((t_cmd *)tmp->content)->pid, NULL, 0);
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

int	exec_cmd_list(t_list *cmd_list, int fd_in, int fd_out)
{
	t_list	*tmp;
	t_cmd	cmd;

	log_msg(DEBUG, "fd_in: %d, fd_out: %d", fd_in, fd_out);
	if (setup_io(fd_in, fd_out) > 0)
		return (SUCCESS);
	tmp = cmd_list;
	while (tmp != NULL && tmp->next != NULL)
	{
		((t_cmd *)tmp->content)->pid = setup_pipe();
		if (((t_cmd *)tmp->content)->pid < 0)
			return (FAILURE);
		if (((t_cmd *)tmp->content)->pid == 0)
		{
			cmd = *((t_cmd *)tmp->content);
			destroy_list(cmd_list);
			exec(cmd);
		}
		tmp = tmp->next;
	}
	((t_cmd *)tmp->content)->pid = fork();
	if (((t_cmd *)tmp->content)->pid < 0)
		return (FAILURE);
	if (((t_cmd *)tmp->content)->pid == 0)
	{
		cmd = *((t_cmd *)tmp->content);
		destroy_list(cmd_list);
		exec(cmd);
	}
	wait_pids(cmd_list);
	destroy_list(cmd_list);
	exit(0);
	return (FAILURE);
}

int	exec_cmd_line(t_list *cmd_list, const char *in_file, const char *out_file)
{
	int	fd_in;
	int	fd_out;

	if (in_file != NULL)
	{
		fd_in = open(in_file, O_RDONLY);
		if (fd_in < 0)
		{
			log_msg(ERROR, "%s: %s", strerror(errno), in_file);
			return (FAILURE);
		}
	}
	else
		fd_in = STDIN_FILENO;
	if (out_file != NULL)
	{
		fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			close(fd_in);
			log_msg(ERROR, "%s: %s", strerror(errno), out_file);
			return (FAILURE);
		}
	}
	else
		fd_out = STDOUT_FILENO;
	exec_cmd_list(cmd_list, fd_in, fd_out);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (SUCCESS);
}
