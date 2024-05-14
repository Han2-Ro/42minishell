/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:46:04 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 14:51:55 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_paths(char **envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

char	*build_path(char *folder, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(folder, "/");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

char	*path_to_bin(char *cmd, t_list *envp)
{
	char	*path;
	char	*env_path;
	char	**folders;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	env_path = get_envvalue(envp, "PATH");
	if (env_path)
		folders = ft_split(env_path, ':');
	else
		folders = NULL;
	while (folders && folders[i])
	{
		path = build_path(folders[i], cmd);
		log_msg(DEBUG, "Checking path: %s", path);
		if (access(path, X_OK) == 0)
			return (free_nullterm_str_arr(folders), path);
		free(path);
		i++;
	}
	free_nullterm_str_arr(folders);
	log_msg(ERROR, "%s: command not found", cmd);
	return (NULL);
}
