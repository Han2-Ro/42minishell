/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:59:50 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/06 16:21:52 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shell_loop(char *envp[])
{
	char *line;
	char *prompt;

	prompt = "ms>";

	while (1)
	{
		line = readline(prompt);
		if (!line)
			break ;
		if (line && *line)
			add_history(line);
		log_msg(DEBUG, "Inputed line: %s\n", line);
		run_cmd(line, envp);
	}
	return (SUCCESS);
}