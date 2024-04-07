/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:46:04 by hrother           #+#    #+#             */
/*   Updated: 2024/04/07 20:27:06 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char *path;
	char **folders;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	folders = ft_split(ft_getenv(envp, "PATH"), ':');
	while (folders && *folders)
	{
		path = build_path(*folders, cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		folders++;
	}
	log_msg(ERROR, "%s: command not found\n", cmd);
	return (NULL);
}