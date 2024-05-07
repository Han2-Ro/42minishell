/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:59:26 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/07 14:00:24 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"
#include "../includes/minishell.h"
#include <stdio.h>

t_token	*lex_pipe(const char *line, unsigned int *i)
{
	t_token	*token;

	(void)line;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = PIPE;
	token->value = NULL;
	(*i)++;
	return (token);
}

int	add_token(t_list **token_lst, const char *line, unsigned int *i,
		t_token *(*lex)(const char *, unsigned int *))
{
	t_list	*new_elm;
	t_token	*token;

	token = lex(line, i);
	if (!token)
	{
		log_msg(ERROR, "Error lexing token %s:%i", __FILE__, __LINE__);
		ft_lstclear(token_lst, free_token);
		return (EXIT_FAILURE);
	}
	new_elm = ft_lstnew(token);
	if (!new_elm)
	{
		log_msg(ERROR, "Malloc failed in ft_lstnew %s:%i", __FILE__, __LINE__);
		ft_lstclear(token_lst, free_token);
		free_token(token);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(token_lst, new_elm);
	return (EXIT_SUCCESS);
}

int	lex_next(const char *line, unsigned int *i, bool *capture_args,
		t_list **token_lst)
{
	int	fail;

	fail = 0;
	if (line[*i] == '|')
	{
		fail += add_token(token_lst, line, i, lex_pipe);
		*capture_args = false;
	}
	else if (ft_strchr("<>", line[*i]))
		fail += add_token(token_lst, line, i, lex_redirect);
	else if (*capture_args)
		fail += add_token(token_lst, line, i, lex_arg);
	else
	{
		fail += add_token(token_lst, line, i, lex_cmd);
		*capture_args = true;
	}
	if (fail > 0)
		return (FAILURE);
	return (SUCCESS);
}

t_list	*lexer(const char *line)
{
	unsigned int	line_len;
	unsigned int	i;
	bool			capture_args;
	t_list			*token_lst;

	token_lst = NULL;
	line_len = ft_strlen(line);
	i = 0;
	capture_args = false;
	while (i < line_len)
	{
		skip_until(line, &i, WHITESPACE, false);
		if (!line[i])
			break ;
		if (lex_next(line, &i, &capture_args, &token_lst) == FAILURE)
			break ;
	}
	return (token_lst);
}
