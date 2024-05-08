/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/05/08 11:37:32 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

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
	ft_lstclear(envlst, free_env);
	if (cmd->bin == NULL)
		(free_nullterm_str_arr(*envp_array), free_cmd(cmd), exit(127));
	if (*envp_array == NULL)
		(free(cmd->bin), free_cmd(cmd), exit(1));
	return (EXIT_SUCCESS);
}

int	exec_cmd(t_cmd *cmd, t_list *cmd_list, t_list **envlst, int status)
{
	char	**envp_array;

	if (cmd->fd_in < 0 || cmd->fd_out < 0 || cmd->bin == NULL)
		return (EXIT_FAILURE);
	if (is_builtin(cmd))
	{
		cmd->status = exec_builtin(cmd, envlst, status);
		return (cmd->status);
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (log_msg(ERROR, "fork: %s", strerror(errno)), EXIT_FAILURE);
	if (cmd->pid > 0)
		return (EXIT_SUCCESS);
	setup_cmd(cmd, envlst, &envp_array);
	ft_lstiter(cmd_list, close_fds);
	log_msg(DEBUG, "executing %s", cmd->bin);
	if (cmd->bin && access(cmd->bin, X_OK) == 0)
		execve(cmd->bin, cmd->args, envp_array);
	exit(127);
	return (EXIT_FAILURE);
}
