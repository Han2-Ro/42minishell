/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:56:30 by hrother           #+#    #+#             */
/*   Updated: 2024/03/25 00:25:14 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*combine_key_value(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	result = ft_strjoin(tmp, value);
	if (result == NULL)
		return (free(tmp), NULL);
	free(tmp);
	return (result);
}

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->value = combine_key_value(key, value);
	if (env->value == NULL)
		return (free(env), NULL);
	return (env);
}

char	*get_value(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		return (arg + i + 1);
	return (NULL);
}

char	*get_key(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	arg[i] = '\0';
	return (arg);
}

int	builtin_export(const t_cmd *cmd, t_list **envp)
{
	t_list	*current;
	t_env	*env;
	char	*key;
	char	*value;

	// TODO: variable count of args
	value = get_value(cmd->args[1]);
	if (!value)
		return (log_msg(ERROR, "export failed"), FAILURE);
	key = get_key(cmd->args[1]);
	current = *envp;
	while (current)
	{
		env = (t_env *)current->content;
		if (ft_strncmp(env->value, key, ft_strlen(key)) == 0)
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
		env->value = combine_key_value(key, value);
	}
	builtin_env(cmd, *envp);
	return (SUCCESS);
}
