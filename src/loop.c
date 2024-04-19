/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:59:50 by aprevrha          #+#    #+#             */
/*   Updated: 2024/04/18 19:50:35 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	shell_loop(t_list *envp)
{
	char	*line;
	char	*prompt;
	t_list	*token_lst;
	t_list	*cmd_lst;
	int		status;

	status = 0;
	prompt = "ms>";
	while (1)
	{
		register_signals();
		if (isatty(STDIN_FILENO))
			line = readline(prompt);
		else
		{
			line = get_next_line(STDIN_FILENO);
			if (line && line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
		}
		log_msg(DEBUG, "Inputed line: %s\n", line);
		if (!line)
			break ;
		if (!*line)
			continue ;
		if (isatty(STDIN_FILENO))
			add_history(line);
		token_lst = lexer(line);
		if (!token_lst)
			log_msg(DEBUG, "Lex: token list null");
		expand_tokens(token_lst, envp, status, false);
		lex_split(&token_lst);
		expand_tokens(token_lst, envp, status, true);
		cmd_lst = parse(token_lst);
		if (!cmd_lst)
		{
			status = 1;
			log_msg(ERROR, "PARSE error");
			free(line);
			ft_lstclear(&token_lst, free_token);
			continue ;
		}
		ft_lstiter(cmd_lst, print_cmd);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		exec_cmd_list(cmd_lst, &envp, &status);
		log_msg(DEBUG, "status: %i", status);
		free(line);
		ft_lstclear(&token_lst, free_token);
	}
	rl_clear_history();
	return (status);
}
