/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:59:50 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/25 16:13:00 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shell_loop(t_list *envp)
{
	char	*line;
	char	*prompt;
	t_list	*token_lst;
	t_list	*cmd_lst;

	register_signals();
	prompt = "ms>";
	while (1)
	{
		line = readline(prompt);
		log_msg(DEBUG, "Inputed line: %s\n", line);
		if (!line)
			break ;
		if (line && *line)
			add_history(line);
		token_lst = lexer(line);
		if (!token_lst)
		{
			log_msg(ERROR, "LEX error");
			continue ;
		}
		cmd_lst = parse(token_lst);
		if (!cmd_lst)
		{
			log_msg(ERROR, "PARSE error");
			free(line);
			ft_lstclear(&token_lst, free_token);
			continue ;
		}
		ft_lstiter(cmd_lst, print_cmd);
		exec_cmd_list(cmd_lst, &envp);
		free(line);
		ft_lstclear(&token_lst, free_token);
	}
	rl_clear_history();
	return (SUCCESS);
}
