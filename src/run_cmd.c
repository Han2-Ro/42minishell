/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:09:20 by hrother           #+#    #+#             */
/*   Updated: 2024/03/06 18:42:18 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * runs a cmd line with realy basic and temporary parsing
 */
int	run_cmd(const char *line, char *envp[])
{
	t_list *cmd_list;
	int result;
	char **tokens;
	char **seperated_by_pipes;

	seperated_by_pipes = ft_split(line, '|');
	int n_pipes = 0;
	while (seperated_by_pipes[n_pipes])
		n_pipes++;
	cmd_list = NULL;
	int i = 0;
	while (i < n_pipes)
	{
		log_msg(DEBUG, "parsing cmd[%i]: %s\n", i, seperated_by_pipes[i]);
		tokens = ft_split(seperated_by_pipes[i], ' ');
		cmd_list = ft_lstadd(&cmd_list, new_cmd(tokens[0], tokens, envp));
		i++;
	}
	result = exec_cmd_list(cmd_list, STDIN_FILENO, STDOUT_FILENO);
	destroy_list(cmd_list);
	return (result);
}