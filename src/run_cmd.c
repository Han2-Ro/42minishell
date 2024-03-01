/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:09:20 by hrother           #+#    #+#             */
/*   Updated: 2024/03/01 15:28:54 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_cmd(const char *line, char *envp[])
{
	t_list *cmd_list;
	int result;
	char **tokens;

	tokens = ft_split(line, ' ');
	cmd_list = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd(tokens[0], tokens, envp));
	result = exec_cmd_list(cmd_list, STDIN_FILENO, STDOUT_FILENO);
	destroy_list(cmd_list);
	return (result);
}