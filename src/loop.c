/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:59:50 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/08 19:15:44 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shell_loop(char *envp[])
{
	char *line;
	char *prompt;
	t_list *token_lst;
	t_list *cmd_lst;

	prompt = "ms>";

	while (1)
	{
		line = readline(prompt);
		if (!line)
			break ;
		if (line && *line)
			add_history(line);
		log_msg(DEBUG, "Inputed line: %s\n", line);

		token_lst = lexer(line);
		if (!token_lst)
		{
			log_msg(ERROR, "LEX error");
			continue ;
		}
		cmd_lst = parse(token_lst, envp);
		exec_cmd_list(cmd_lst, STDIN_FILENO, STDOUT_FILENO);

		// run_cmd(line, envp);
	}
	return (SUCCESS);
}