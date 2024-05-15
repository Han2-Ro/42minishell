/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 22:32:06 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	setup_pipes(t_list *cmd_list)
{
	t_list	*current_cmd;
	int		pipe_fds[2];

	current_cmd = cmd_list;
	while (current_cmd != NULL && current_cmd->next != NULL)
	{
		if (pipe(pipe_fds) != SUCCESS)
			return (log_msg(ERROR, "pipe: %s", strerror(errno)), FAILURE);
		((t_cmd *)current_cmd->content)->fd_out = pipe_fds[1];
		((t_cmd *)current_cmd->next->content)->fd_in = pipe_fds[0];
		current_cmd = current_cmd->next;
	}
	return (SUCCESS);
}

int	wait_pids(t_list *cmd_list)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = cmd_list;
	while (tmp != NULL)
	{
		cmd = (t_cmd *)tmp->content;
		log_msg(DEBUG, "waiting for pid: %d", cmd->pid);
		if (((t_cmd *)tmp->content)->pid > 0)
		{
			waitpid(cmd->pid, &((t_cmd *)tmp->content)->status, 0);
			cmd->status = WEXITSTATUS(((t_cmd *)tmp->content)->status);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void	free_exec_cmd_list(char **envp_array, t_list **cmd_list)
{
	free_nullterm_str_arr(envp_array);
	ft_lstclear(cmd_list, free_cmd);
}

int	exec_cmd_list(t_list *cmd_list, t_evars *evars)
{
	t_list	*current_cmd;
	char	**envp_array;

	envp_array = envlst_to_envp(evars->envl);
	if (setup_pipes(cmd_list) != SUCCESS || redirs_to_fds(cmd_list,
			evars) != SUCCESS)
		return (free_exec_cmd_list(envp_array, &cmd_list), FAILURE);
	current_cmd = cmd_list;
	while (current_cmd != NULL)
	{
		exec_cmd((t_cmd *)current_cmd->content, cmd_list, evars, envp_array);
		if (((t_cmd *)current_cmd->content)->pid == 0)
			break ;
		if (current_cmd->next == NULL)
			break ;
		current_cmd = current_cmd->next;
	}
	ft_lstiter(cmd_list, close_fds);
	wait_pids(cmd_list);
	evars->status = ((t_cmd *)current_cmd->content)->status;
	free_exec_cmd_list(envp_array, &cmd_list);
	return (SUCCESS);
}
