/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/05/12 17:53:26 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
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

int	setup_cmd(t_cmd *cmd, t_list **envlst, char ***envp_array)
{
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	cmd->bin = path_to_bin(cmd->bin, *envlst);
	*envp_array = envlst_to_envp(*envlst);
	if (cmd->bin == NULL)
		(free_nullterm_str_arr(*envp_array), cmd->status = 127);
	if (*envp_array == NULL)
		(free(cmd->bin), cmd->status = 1);
	return (EXIT_SUCCESS);
}

int	try_exec_path(t_cmd *cmd, char **envp_array)
{
	struct stat	s_pstat;

	if (stat(cmd->bin, &s_pstat) == -1)
		log_msg(ERROR, strerror(errno));
	else if (S_ISDIR(s_pstat.st_mode))
	{
		log_msg(ERROR, "Is a Directory");
		cmd->status = EXIT_MASK | 126;
		return(126);
	}
	if (cmd->bin && access(cmd->bin, X_OK) == 0)
	{
		execve(cmd->bin, cmd->args, envp_array);
		log_msg(ERROR, "%s: %s", cmd->bin, strerror(errno));
		cmd->status = EXIT_MASK | 126;
		return(126);
	}
	cmd->status = EXIT_MASK | 127;
	return(127);
}

int	exec_cmd(t_cmd *cmd, t_list *cmd_list, t_evars *evars)
{
	char	**envp_array;

	if (cmd->fd_in < 0 || cmd->fd_out < 0 || cmd->bin == NULL)
		return (EXIT_FAILURE);
	if (is_builtin(cmd))
	{
		cmd->status = exec_builtin(cmd, &evars->envp, evars->status);
		return (cmd->status);
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (log_msg(ERROR, "fork: %s", strerror(errno)), EXIT_FAILURE);
	if (cmd->pid > 0)
		return (EXIT_SUCCESS);
	setup_cmd(cmd, &evars->envp, &envp_array);
	ft_lstiter(cmd_list, close_fds);
	log_msg(DEBUG, "executing %s", cmd->bin);
	try_exec_path(cmd, envp_array);
	cmd->status = EXIT_MASK | cmd->status;
	return (EXIT_FAILURE);
}
