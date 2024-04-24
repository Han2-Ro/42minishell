/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:59:50 by aprevrha          #+#    #+#             */
/*   Updated: 2024/04/24 16:18:57 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_readline(char *prompt)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline(prompt);
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
	}
	log_msg(DEBUG, "Inputed line: %s", line);
	return (line);
}

int	process_line(char *line, int status, t_list *env_list)
{
	t_list	*token_lst;
	t_list	*cmd_lst;

	token_lst = lexer(line);
	expand_tokens_new(token_lst, env_list, status);
	if (!token_lst)
		log_msg(DEBUG, "Lex: token list null");
	cmd_lst = parse(token_lst);
	if (!cmd_lst)
	{
		log_msg(ERROR, "PARSE error");
		ft_lstclear(&token_lst, free_token);
		return (1);
	}
	ft_lstiter(cmd_lst, print_cmd);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	exec_cmd_list(cmd_lst, &env_list, &status);
	log_msg(DEBUG, "status: %i", status);
	ft_lstclear(&token_lst, free_token);
	return (status);
}

int	shell_loop(t_list *env_list)
{
	char	*line;
	int		status;

	status = 0;
	while (1)
	{
		register_signals();
		line = ft_readline(PROMPT);
		if (!line)
			break ;
		if (!*line)
			continue ;
		if (isatty(STDIN_FILENO))
			add_history(line);
		status = process_line(line, status, env_list);
		free(line);
	}
	rl_clear_history();
	return (status);
}
