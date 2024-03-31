/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:00:29 by hrother           #+#    #+#             */
/*   Updated: 2024/03/31 16:55:49 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_env(const t_cmd *cmd, t_list **envp)
{
	t_env *env;
	t_list *current;

	(void)cmd;
	current = *envp;
	while (current != NULL)
	{
		env = (t_env *)(current)->content;
		ft_printf("%s=%s\n", env->key, env->value);
		current = current->next;
	}
	return (SUCCESS);
}