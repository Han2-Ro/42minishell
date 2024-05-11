/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:24 by hrother           #+#    #+#             */
/*   Updated: 2024/05/11 13:38:44 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	print_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	log_msg(ERROR, "%s=%s", env->key, env->value);
}

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

char	*ft_getenv(const t_list *envlst, const char *key)
{
	t_env	*env;
	int		len_key;
	int		len_env_key;

	if (key == NULL)
		return (NULL);
	len_key = ft_strlen(key);
	log_msg(DEBUG, "search key: %s", key);
	while (envlst != NULL)
	{
		env = (t_env *)envlst->content;
		len_env_key = ft_strlen(env->key);
		if (len_key == len_env_key && ft_strncmp(env->key, key, len_key) == 0)
			return (env->value);
		envlst = envlst->next;
	}
	return (NULL);
}
