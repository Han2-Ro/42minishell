/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:56:30 by hrother           #+#    #+#             */
/*   Updated: 2024/04/14 14:14:52 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// TODO: variable count of args
int	builtin_export(const t_cmd *cmd, t_list **envp)
{
	t_list	*current;
	t_env	*env;
	char	*key;
	char	*value;

	value = get_value(cmd->args[1]);
	if (!value)
		return (log_msg(ERROR, "malloc failed"), FAILURE);
	key = get_key(cmd->args[1]);
	current = *envp;
	while (current)
	{
		env = (t_env *)current->content;
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			break ;
		current = current->next;
	}
	if (current == NULL)
	{
		env = new_env(key, value);
		if (env == NULL)
			return (log_msg(ERROR, "malloc failed"), FAILURE);
		ft_lstadd_back(envp, ft_lstnew(env));
	}
	else
	{
		free(env->value);
		env->value = value;
	}
	return (SUCCESS);
}
