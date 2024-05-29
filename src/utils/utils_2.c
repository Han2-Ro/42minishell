/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/27 21:30:28 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <sys/types.h>

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
