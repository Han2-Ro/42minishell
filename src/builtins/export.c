/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:56:30 by hrother           #+#    #+#             */
/*   Updated: 2024/04/22 18:15:37 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	split_key_val(const char *key_val_pair, char **key, char **value)
{
	*value = get_value(key_val_pair);
	if (!*value)
		return (log_msg(ERROR, "malloc failed"), FAILURE);
	*key = get_key(key_val_pair);
	if (!*value)
		return (log_msg(ERROR, "malloc failed"), free(*value), FAILURE);
	return (SUCCESS);
}

bool	key_is_valid(char *key)
{
	int i;
	
	if (ft_isdigit(key[0]))
		return (false);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

//stupid 25line
int export_var2(t_list **envp, char *key, char *value)
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
	else
	{
		free(env->value);
		env->value = value;
	}
	return(SUCCESS);
}

int export_var(const char *key_val_pair, t_list **envp)
{
	
	
	char	*key;
	char	*value;

	if (split_key_val(key_val_pair, &key, &value) == FAILURE)
		return (FAILURE);
	if (!key_is_valid(key))
		return (log_msg(ERROR, "invalid key '%s'", key), FAILURE);
	
	return (export_var2(envp, key, value));
}

t_env	**fill_env_arr(t_list *envp, int size)
{
	t_list	*curr;
	t_env	**envs;
	int		i;

	
	envs = malloc(sizeof(t_env *) * size);
	if (envs == NULL)
		return (log_msg(ERROR, "malloc failed"), NULL);
	
	curr = envp;
	i = 0;
	while (curr != NULL && i < size)
	{
		envs[i] = curr->content;
		curr = curr->next;
		i++;
	}
	return (envs);
}

void sort_env_arr(t_env **envs, int size)
{
	int i;
	t_env *temp;
	bool sorted;

	sorted = false;
	while (!sorted)
	{
		sorted = true;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(envs[i]->key, envs[i + 1]->key) > 0)
			{
				temp = envs[i];
				envs[i] = envs[i + 1];
				envs[i + 1] = temp;
				sorted = false;
			}
			i++;
			//printf("%s\n", envs[i]->key);
		}
	}
}

void print_export(t_list **envp)
{
	t_env	**envs;
	int		i;
	int		size;

	size = ft_lstsize(*envp);
	envs = fill_env_arr(*envp, size);
	if (!envs)
		return;
	sort_env_arr(envs, size);
	i = 0;
	while (i < size)
	{
		printf("declare -x %s=\"%s\"\n", envs[i]->key, envs[i]->value);
		i++;
	}
	free(envs);
}

int	builtin_export(const t_cmd *cmd, t_list **envp)
{
	int		i;

	if (!cmd->args[1])
	{
		//print envlist: declare -x MY_VARIABLE="some_value"
		print_export(envp);
	}
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (export_var(cmd->args[i], envp) == FAILURE)
				log_msg(ERROR, "Failed to export '%s'", cmd->args[i]);
			i++;
		}
	}
	return (SUCCESS);
}
