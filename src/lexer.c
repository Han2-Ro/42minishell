/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:59:26 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/13 17:54:01 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

// TODO: Clear the list logic
void	free_tokenlst(t_list *tokenlst)
{
	(void)tokenlst;
	log_msg(WARNING, "lexer had to clear token list, something went wrong...");
}

static void	skip_until(const char *str, unsigned int *i, const char *charset,
		bool val)
{
	while ((ft_strchr(charset, str[*i]) != 0) != val && str[*i] != '\0')
		*i += 1;
}

t_token	*lex_cmd(const char *line, unsigned int *i)
{
	t_token			*token;
	unsigned int	lex_len;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	lex_len = 0;
	skip_until(&line[*i], &lex_len, " |<>", true);
	token->type = CMD;
	token->value = ft_substr(line, *i, lex_len);
	if (!(token->value))
		return (free(token), NULL);
	*i += lex_len;
	return (token);
}

static unsigned int	arg_len(const char *arg)
{
	unsigned int	len;
	unsigned int	add;

	len = 0;
	add = 0;
	while (true)
	{
		if (arg[len] == '\'')
		{
			len++;
			skip_until(arg, &len, "\'", true);
			len++;
		}
		else if (arg[len] == '\"')
		{
			len++;
			skip_until(arg, &len, "\"", true);
			len++;
		}
		else if (!ft_strchr(" <>|", arg[len]))
			skip_until(arg, &len, "\"\' <>|", true);
		else
			return (len);
	}
}

t_token	*lex_arg(const char *line, unsigned int *i)
{
	t_token			*token;
	unsigned int	lex_len;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	lex_len = 0;
	lex_len = arg_len(&line[*i]);
	token->type = ARG;
	token->value = ft_substr(line, *i, lex_len);
	if (!(token->value))
		return (free(token), NULL);
	*i += lex_len;
	return (token);
}

t_token_type	redirect_type(const char *redir_str, unsigned int *i)
{
	if (redir_str[0] == '>' && redir_str[1] == '>' && !ft_strchr("<>",
			redir_str[2]))
		return (*i += 2, R_APPEND);
	else if (redir_str[0] == '>' && !ft_strchr("<>", redir_str[1]))
		return (*i += 1, R_OUT);
	else if (redir_str[0] == '<' && redir_str[1] == '<' && !ft_strchr("<>",
			redir_str[2]))
		return (*i += 2, R_HEREDOC);
	else if (redir_str[0] == '<' && !ft_strchr("<>", redir_str[1]))
		return (*i += 1, R_IN);
	else
		return (log_msg(ERROR, "Wrong redirect syntax!"), NOTDEF);
}

t_token	*lex_redirect(const char *line, unsigned int *i)
{
	t_token			*token;
	unsigned int	lex_len;
	t_token_type	redir_type;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	lex_len = 0;
	redir_type = redirect_type(&line[*i], i);
	if (redir_type == NOTDEF)
		return (free(token), NULL);
	token->type = redir_type;
	// skip_until(line, i, "<>", false);
	if (line[*i] == ' ')
		skip_until(line, i, " ", false);
	skip_until(&line[*i], &lex_len, " <>|", true);
	token->value = ft_substr(line, *i, lex_len);
	if (!(token->value))
		return (free(token), NULL);
	*i += lex_len;
	return (token);
}

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

// TODO: Handle error: "lex retured NULL"
// TODO: Fix bugs
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
		skip_until(line, &i, " ", false);
		if (line[i] == '|')
		{
			ft_lstadd_back(&token_lst, ft_lstnew(lex_pipe(line, &i)));
			capture_args = false;
		}
		else if (ft_strchr("<>", line[i]))
			ft_lstadd_back(&token_lst, ft_lstnew(lex_redirect(line, &i)));
		else if (capture_args)
			ft_lstadd_back(&token_lst, ft_lstnew(lex_arg(line, &i)));
		else
		{
			ft_lstadd_back(&token_lst, ft_lstnew(lex_cmd(line, &i)));
			capture_args = true;
		}
	}
	ft_lstiter(token_lst, expand);
	return (token_lst);
}
