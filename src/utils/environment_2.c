/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:24 by hrother           #+#    #+#             */
/*   Updated: 2024/06/09 11:27:57 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new env object
 * @param key allocated string (will be freed if this function fails)
 * @param value allocated string (will be freed if this function fails)
 * @return new env object or NULL if malloc failed
 */
t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (free(key), free(value), NULL);
	env->key = key;
	env->value = value;
	return (env);
}

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	if (env == NULL)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

const t_list	*find_env(const t_list *list, const char *key)
{
	t_env			*env;
	const t_list	*finding;

	log_msg(DEBUG, "search key: %s", key);
	if (key == NULL)
		return (NULL);
	finding = list;
	while (finding)
	{
		env = (t_env *)finding->content;
		if (ft_strcmp(env->key, key) == 0)
			break ;
		finding = finding->next;
	}
	return (finding);
}

char	*get_envvalue(const t_list *envlst, const char *key)
{
	t_env			*env;
	const t_list	*finding;

	finding = find_env(envlst, key);
	if (finding == NULL)
		return (NULL);
	env = (t_env *)finding->content;
	return (env->value);
}
