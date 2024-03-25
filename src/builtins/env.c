/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:00:29 by hrother           #+#    #+#             */
/*   Updated: 2024/03/25 00:24:49 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_env(const t_cmd *cmd, const t_list *envp)
{
	t_env *env;

	while (envp)
	{
		env = (t_env *)envp->content;
		ft_putendl_fd(env->value, cmd->fd_out);
		envp = envp->next;
	}
	return (SUCCESS);
}