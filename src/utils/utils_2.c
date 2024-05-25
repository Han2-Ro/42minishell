/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/25 16:50:33 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>
#include <sys/types.h>

// TODO: Do we even need this anymore?
bool	fd_is_pipe(int fd)
{
	struct stat	buf;

	fstat(fd, &buf);
	if (S_ISFIFO(buf.st_mode))
		return (true);
	else
		return (false);
}

/**
 * @brief This is only used in exit, cd,
	export and unset to see if we should not run a command
 */
bool	dont_run(const t_cmd *cmd)
{
	if (cmd->is_pipeline)
		return (true);
	else
		return (false);
}

void	set_is_pipeline(t_list *cmds)
{
	log_msg(DEBUG, "set_is_pipeline called");
	if (!cmds)
		return ;
	if (cmds->next)
	{
		log_msg(DEBUG, "set is_pipeline 1");
		while (cmds)
		{
			((t_cmd *)(cmds->content))->is_pipeline = 1;
			cmds = cmds->next;
		}
	}
	else
		((t_cmd *)(cmds->content))->is_pipeline = 0;
}
