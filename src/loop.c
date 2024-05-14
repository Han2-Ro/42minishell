/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:59:50 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/14 23:28:32 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_readline(char *prompt, int tty)
{
	char	*line;

	if (tty)
		line = readline(prompt);
	else
	{
		line = read_next_line(STDIN_FILENO);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
	}
	log_msg(DEBUG, "Inputed line: %s", line);
	return (line);
}

void	handle_sig(int sig)
{
	log_msg(INFO, "SIG:%i\n", sig);
}

int	process_line(char *line, t_evars *evars)
{
	t_list	*token_lst;
	t_list	*cmd_lst;

	token_lst = lexer(line, &(evars->status));
	if (!token_lst)
		return (evars->status);
	expand_token_list(&token_lst, *evars);
	if (!token_lst)
		log_msg(DEBUG, "Lex: token list null");
	cmd_lst = parse(token_lst);
	if (!cmd_lst)
	{
		log_msg(ERROR, "PARSE error");
		ft_lstclear(&token_lst, free_token);
		return (2);
	}
	ft_lstiter(cmd_lst, print_cmd);
	active_signals();
	exec_cmd_list(cmd_lst, evars);
	log_msg(DEBUG, "status: %i", evars->status);
	ft_lstclear(&token_lst, free_token);
	return (evars->status);
}

int	shell_loop(t_list *env_list, int tty)
{
	char	*line;
	t_evars	evars;

	evars.status = 0;
	evars.tty = tty;
	evars.envl = env_list;
	while (1)
	{
		idle_signals();
		line = ft_readline(PROMPT, tty);
		if (!line)
			break ;
		if (!*line)
			continue ;
		if (tty)
			add_history(line);
		evars.status = process_line(line, &evars);
		free(line);
		if (evars.status & EXIT_MASK)
			break ;
	}
	rl_clear_history();
	return (evars.status & STATUS_MASK);
}
