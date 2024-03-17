/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/03/17 18:19:53 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	exec(t_cmd cmd, t_list **envp)
{
	char	**envp_array;

	envp_array = envlst_to_envp(*envp);
	if (envp_array == NULL)
		exit(1);
	if (cmd.fd_in < 0 || cmd.fd_out < 0)
		exit(1);
	if (cmd.fd_in > 2)
		dup2(cmd.fd_in, STDIN_FILENO);
	if (cmd.fd_out > 2)
		dup2(cmd.fd_out, STDOUT_FILENO);
	exec_builtin(cmd, envp);
	cmd.bin = path_to_bin(cmd.bin);
	log_msg(INFO, "executing %s", cmd.bin);
	if (access(cmd.bin, X_OK) == 0)
		execve(cmd.bin, cmd.args, envp_array);
	log_msg(ERROR, "%s: %s", cmd.bin, strerror(errno));
	exit(1);
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

void	log_file_error(const char *filename)
{
	log_msg(ERROR, "%s: %s", filename, strerror(errno));
}

int	run_in_child(void)
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
	return (pid);
}

int	exec_cmd_list(t_list *cmd_list, t_list **envp)
{
	t_list	*tmp;
	t_cmd	cmd;

	if (run_in_child() > 0)
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
			ft_lstclear(&cmd_list, free); // TODO: check if everything is freed
			exec(cmd, envp);
		}
		tmp = tmp->next;
	}
	((t_cmd *)tmp->content)->pid = fork();
	if (((t_cmd *)tmp->content)->pid < 0)
		return (FAILURE);
	if (((t_cmd *)tmp->content)->pid == 0)
	{
		cmd = *((t_cmd *)tmp->content);
		ft_lstclear(&cmd_list, free); // TODO: check if everything is freed
		exec(cmd, envp);
	}
	wait_pids(cmd_list);
	ft_lstclear(&cmd_list, free_cmd);
	exit(0);
	return (FAILURE);
}
