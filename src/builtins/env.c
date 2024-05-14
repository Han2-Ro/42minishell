/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:00:29 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 22:15:30 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(const t_cmd *cmd, t_list **envp)
{
	t_env	*env;
	t_list	*current;
	int		argc;

	argc = 0;
	while (cmd->args[argc] != NULL)
		argc++;
	if (argc > 1)
		return (log_msg(ERROR, "env: " MSG_WRONG_ARGC), 1);
	current = *envp;
	while (current != NULL)
	{
		env = (t_env *)(current)->content;
		if (env->value != NULL)
		{
			ft_putstr_fd(env->key, cmd->fd_out);
			ft_putchar_fd('=', cmd->fd_out);
			ft_putstr_fd(env->value, cmd->fd_out);
			ft_putchar_fd('\n', cmd->fd_out);
		}
		current = current->next;
	}
	return (SUCCESS);
}
