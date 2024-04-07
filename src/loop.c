/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:59:50 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/26 15:01:17 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shell_loop(t_list *envp)
{
	char	*line;
	char	*prompt;
	t_list	*token_lst;
	t_list	*cmd_lst;

	
	prompt = "ms>";
	while (1)
	{
		register_signals();
		line = readline(prompt);
		log_msg(DEBUG, "Inputed line: %s\n", line);
		if (!line)
			break ;
		if (!*line)
			continue ;
		add_history(line);
		token_lst = lexer(line);
		if (!token_lst)
			log_msg(DEBUG, "Lex: token list null");
		cmd_lst = parse(token_lst);
		if (!cmd_lst)
		{
			log_msg(ERROR, "PARSE error");
			free(line);
			ft_lstclear(&token_lst, free_token);
			continue ;
		}
		ft_lstiter(cmd_lst, print_cmd);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		exec_cmd_list(cmd_lst, &envp);
		free(line);
		ft_lstclear(&token_lst, free_token);
	}
	rl_clear_history();
	return (SUCCESS);
}
