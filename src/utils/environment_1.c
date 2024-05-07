/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:24 by hrother           #+#    #+#             */
<<<<<<< HEAD:src/environment.c
/*   Updated: 2024/05/03 15:13:58 by hrother          ###   ########.fr       */
=======
/*   Updated: 2024/05/06 22:08:47 by aprevrha         ###   ########.fr       */
>>>>>>> main:src/utils/environment_1.c
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

<<<<<<< HEAD:src/environment.c
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

=======
>>>>>>> main:src/utils/environment_1.c
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
