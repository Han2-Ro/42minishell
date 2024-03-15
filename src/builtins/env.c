/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:00:29 by hrother           #+#    #+#             */
/*   Updated: 2024/03/15 16:32:18 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_env(const t_list *envp)
{
	t_env *env;

	while (envp)
	{
		env = (t_env *)envp->content;
		ft_putendl_fd(env->value, STDOUT_FILENO);
		envp = envp->next;
	}
	return (SUCCESS);
}