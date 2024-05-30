/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/05/30 17:49:07 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void	close_fds(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
}

int	setup_fds(t_cmd *cmd)
{
	bool	success;

	success = true;
	if (cmd->fd_in > 2)
		success = dup2(cmd->fd_in, STDIN_FILENO) >= 0;
	if (cmd->fd_out > 2)
		success &= dup2(cmd->fd_out, STDOUT_FILENO) >= 0;
	if (success)
		return (EXIT_SUCCESS);
	log_msg(ERROR, "dup2: %s", strerror(errno));
	return (EXIT_FAILURE);
}

int	check_bin(char *bin)
{
	struct stat	s_pstat;

	if (bin == NULL)
		return (127);
	if (stat(bin, &s_pstat) == -1)
	{
		log_msg(ERROR, strerror(errno));
		return (FAILURE);
	}
	else if (S_ISDIR(s_pstat.st_mode))
	{
		log_msg(ERROR, "Is a Directory");
		return (126);
	}
	return (SUCCESS);
}

int	exec_child(t_cmd *cmd, t_list *cmd_list, char **envp_array, t_evars *evars)
{
	evars->state = CHILD;
	reset_signals();
	setup_fds(cmd);
	(void)cmd_list;
	ft_lstiter(cmd_list, close_fds);
	if (is_builtin(cmd))
	{
		cmd->fd_in = STDIN_FILENO;
		cmd->fd_out = STDOUT_FILENO;
		cmd->status = exec_builtin(cmd, &evars->envl, evars->status);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		return (cmd->status);
	}
	cmd->status = check_bin(cmd->bin);
	if (cmd->status != SUCCESS)
		return (cmd->status);
	log_msg(DEBUG, "executing %s", cmd->bin);
	execve(cmd->bin, cmd->args, envp_array);
	log_msg(ERROR, "execve: %s: %s", cmd->bin, strerror(errno));
	return (FAILURE);
}

int	exec_cmd(t_cmd *cmd, t_list *cmd_list, t_evars *evars, char **envp_array)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0 || cmd->args[0] == NULL)
		return (FAILURE);
	if (is_builtin(cmd))
	{
		if (cmd->is_pipeline == 0)
		{
			cmd->status = exec_builtin(cmd, &evars->envl, evars->status);
			return (cmd->status);
		}
	}
	else
	{
		cmd->bin = path_to_bin(cmd->args[0], evars->envl);
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (log_msg(ERROR, "fork: %s", strerror(errno)), FAILURE);
	if (cmd->pid > 0)
		return (SUCCESS);
	return (exec_child(cmd, cmd_list, envp_array, evars));
}
