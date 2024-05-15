/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:59:50 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/15 21:08:07 by aprevrha         ###   ########.fr       */
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

char	*get_prompt(t_evars *evars)
{
	char	*prompt;
	char	*temp;
	char	*pwd;
	char	*home;
	char	*end;

	end = "\033[32m > \033[0m";
	if (evars->status != 0)
		end = "\033[31m > \033[0m";
	prompt = NULL;
	pwd = get_envvalue(evars->envl, "PWD");
	home = get_envvalue(evars->envl, "HOME");
	temp = pwd;
	if (!ft_strncmp(home, pwd, ft_strlen(home)))
	{
		temp += ft_strlen(home);
		prompt = vstrjoin(3, "\033[36m~", temp, end);
	}
	else
		prompt = vstrjoin(3, "\033[36m", temp, end);
	return (prompt);
}

char	*get_line(t_evars *evars)
{
	char	*line;
	char	*prompt;

	prompt = NULL;
	if (evars->tty)
		prompt = get_prompt(evars);
	if (prompt)
	{
		line = ft_readline(prompt, evars->tty);
		free(prompt);
	}
	else
		line = ft_readline(PROMPT, evars->tty);
	return (line);
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
		line = get_line(&evars);
		idle_signals();
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
