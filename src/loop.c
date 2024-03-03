/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:59:50 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/03 18:24:28 by aprevrha         ###   ########.fr       */
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
		if (line && *line)
			add_history(line);
		log_msg(DEBUG, "Inputed line: %s\n", line);
		run_cmd(line, envp);
	}
}