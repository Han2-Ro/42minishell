/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:24 by hrother           #+#    #+#             */
/*   Updated: 2024/05/07 15:39:42 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*combine_key_value(char *key, char *value)
{
	char	*tmp;
	char	*result;

	if (value == NULL)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

char	*get_value(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		return (ft_substr(arg, i + 1, ft_strlen(arg)));
	return (NULL);
}

char	*get_key(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i));
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
		env = malloc(sizeof(t_env));
		if (env == NULL)
			return (ft_lstclear(&lst, free_env), NULL);
		env->key = get_key(envp[i]);
		env->value = get_value(envp[i]);
		new = ft_lstnew(env);
		if (new == NULL || env->key == NULL)
			return (free_env(env), free(new), ft_lstclear(&lst, free_env),
				NULL);
		ft_lstadd_back(&lst, new);
		i++;
	}
	return (lst);
}

char	**envlst_to_envp(t_list *envlst)
{
	int		i;
	char	**envp;
	int		listlen;

	listlen = ft_lstsize(envlst);
	envp = (char **)malloc(sizeof(char *) * (listlen + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (i < listlen)
	{
		envp[i] = combine_key_value(((t_env *)envlst->content)->key,
				((t_env *)envlst->content)->value);
		if (envp[i] == NULL)
			return (free_str_arr(envp, i), NULL);
		envlst = envlst->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
