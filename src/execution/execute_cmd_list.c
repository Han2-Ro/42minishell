/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:21:59 by hrother           #+#    #+#             */
/*   Updated: 2024/04/30 19:22:21 by aprevrha         ###   ########.fr       */
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

int	exec_cmd_list(t_list *cmd_list, t_evars *evars)
{
	t_list	*current_cmd;

	if (setup_pipes(cmd_list) != EXIT_SUCCESS || redirs_to_fds(cmd_list, evars) != EXIT_SUCCESS)
		return (ft_lstclear(&cmd_list, free_cmd), EXIT_FAILURE);
	current_cmd = cmd_list;
	while (current_cmd != NULL)
	{
		exec_cmd((t_cmd *)current_cmd->content, cmd_list, &(evars->envp), evars->status);
		current_cmd = current_cmd->next;
	}
	ft_lstiter(cmd_list, close_fds);
	wait_pids(cmd_list);
	evars->status = ((t_cmd *)ft_lstlast(cmd_list)->content)->status;
	ft_lstclear(&cmd_list, free_cmd);
	return (EXIT_SUCCESS);
}
