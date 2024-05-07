/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:56:30 by hrother           #+#    #+#             */
/*   Updated: 2024/05/06 22:29:42 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	**fill_env_arr(t_list *envp, int size)
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

static void	sort_env_arr(t_env **envs, int size)
{
	int		i;
	t_env	*temp;
	bool	sorted;

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
		}
	}
}

// print envlist: declare -x MY_VARIABLE="some_value"
void	print_export(t_list **envp, int fd)
{
	t_env	**envs;
	int		i;
	int		size;

	size = ft_lstsize(*envp);
	envs = fill_env_arr(*envp, size);
	if (!envs)
		return ;
	sort_env_arr(envs, size);
	i = 0;
	while (i < size)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(envs[i]->key, fd);
		if (envs[i]->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(envs[i]->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putchar_fd('\n', fd);
		i++;
	}
	free(envs);
}
