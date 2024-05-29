/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:56:30 by hrother           #+#    #+#             */
/*   Updated: 2024/05/27 21:30:46 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_list **envp, int fd);

int	split_key_val(const char *key_val_pair, char **key, char **value)
{
	*value = get_value(key_val_pair);
	*key = get_key(key_val_pair);
	if (!*key)
		return (log_msg(ERROR, "malloc failed"), free(*value), FAILURE);
	return (SUCCESS);
}

bool	key_is_valid(char *key)
{
	int	i;

	if (ft_isdigit(key[0]))
		return (false);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	if (i > 0)
		return (true);
	return (false);
}

int	export_env_var(t_list **envp, char *key, char *value)
{
	const t_list	*current;
	t_env			*env;
	t_list			*new;

	current = find_env(*envp, key);
	if (current == NULL)
	{
		env = new_env(key, value);
		if (env == NULL)
			return (log_msg(ERROR, "malloc failed"), FAILURE);
		new = ft_lstnew(env);
		if (new == NULL)
			return (free_env(env), log_msg(ERROR, "malloc failed"), FAILURE);
		ft_lstadd_back(envp, new);
	}
	else if (value != NULL)
	{
		env = (t_env *)current->content;
		free(key);
		free(env->value);
		env->value = value;
	}
	else
		free(key);
	return (SUCCESS);
}

int	export_key_val_pair(const char *key_val_pair, t_list **envp)
{
	char	*key;
	char	*value;

	if (split_key_val(key_val_pair, &key, &value) == FAILURE)
		return (FAILURE);
	if (!key_is_valid(key))
		return (free(key), free(value), FAILURE);
	return (export_env_var(envp, key, value));
}

int	builtin_export(const t_cmd *cmd, t_list **envp)
{
	int	i;

	if (!cmd->args[1])
	{
		print_export(envp, cmd->fd_out);
	}
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (export_key_val_pair(cmd->args[i], envp) == FAILURE)
				return (log_msg(ERROR, "export: `%s': not a valid identifier",
						cmd->args[i]), 1);
			i++;
		}
	}
	return (SUCCESS);
}
