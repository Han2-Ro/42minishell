/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:24 by hrother           #+#    #+#             */
/*   Updated: 2024/03/31 16:40:07 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	log_msg(DEBUG, "%s=%s", env->key, env->value);
}

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

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
	env->key = key;
	env->value = value;
	return (env);
}

char	*get_value(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		return (ft_substr(arg, i + 1, ft_strlen(arg)));
	return (NULL);
}

char	*get_key(char *arg)
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
		env = new_env(get_key(envp[i]), get_value(envp[i]));
		if (env == NULL)
			return (ft_lstclear(&lst, free_env), NULL);
		log_msg(DEBUG, "envp_to_list: %p key:%s value:%s", env, env->key, env->value);
		new = ft_lstnew(env);
		if (new == NULL)
			return (free_env(env), ft_lstclear(&lst, free_env), NULL);
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
		envp[i] = combine_key_value(((t_env *)envlst->content)->key, ((t_env *)envlst->content)->value);
		if (envp[i] == NULL)
			return (free_str_arr(envp, i), NULL);
		envlst = envlst->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
