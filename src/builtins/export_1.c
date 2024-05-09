/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:56:30 by hrother           #+#    #+#             */
/*   Updated: 2024/05/09 13:13:44 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// stupid 25line
int	export_var2(t_list **envp, char *key, char *value)
{
	t_list	*current;
	t_env	*env;

	current = *envp;
	while (current)
	{
		env = (t_env *)current->content;
		if (ft_strcmp(env->key, key) == 0)
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
	else if (value != NULL)
	{
		free(env->value);
		env->value = value;
	}
	return (SUCCESS);
}

int	export_var(const char *key_val_pair, t_list **envp)
{
	char	*key;
	char	*value;

	if (split_key_val(key_val_pair, &key, &value) == FAILURE)
		return (FAILURE);
	if (!key_is_valid(key))
		return (log_msg(ERROR, "invalid key '%s'", key), FAILURE);
	return (export_var2(envp, key, value));
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
			if (export_var(cmd->args[i], envp) == FAILURE)
				return (log_msg(ERROR, "Failed to export '%s'", cmd->args[i]),
					1);
			i++;
		}
	}
	return (SUCCESS);
}
