/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:24 by hrother           #+#    #+#             */
/*   Updated: 2024/03/06 17:53:40 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	log_msg(DEBUG, "%s", env->value);
}

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->value);
	free(env);
}

t_list	*envp_to_list(char **envp)
{
	t_list	*lst;
	t_env	*env;
	t_list	*new;
	int		i;

	lst = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		env = (t_env *)malloc(sizeof(t_env));
		if (env == NULL)
			return (ft_lstclear(&lst, free_env), NULL);
		env->value = ft_strdup(envp[i]);
		if (env->value == NULL)
			return (free(env), ft_lstclear(&lst, free_env), NULL);
		new = ft_lstnew(env);
		if (new == NULL)
			return (free_env(env), ft_lstclear(&lst, free_env), NULL);
		ft_lstadd_back(&lst, new);
		i++;
	}
	return (lst);
}
