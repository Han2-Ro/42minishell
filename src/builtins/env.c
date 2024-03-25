/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:00:29 by hrother           #+#    #+#             */
/*   Updated: 2024/03/25 18:14:42 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_env(const t_cmd *cmd, t_list **envp)
{
	t_env *env;
	t_list *current;

	current = *envp;
	while (current != NULL)
	{
		env = (t_env *)(current)->content;
		ft_putendl_fd(env->value, cmd->fd_out);
		current = current->next;
	}
	return (SUCCESS);
}