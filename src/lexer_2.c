/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:46:13 by aprevrha          #+#    #+#             */
/*   Updated: 2024/06/09 11:23:34 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	arg_len(const char *arg)
{
	unsigned int	len;

	len = 0;
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
		else if (!ft_strchr(WHITESPACE "<>|", arg[len]))
			skip_until(arg, &len, WHITESPACE "\"\'<>|", true);
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

static t_token_type	redirect_type(const char *redir_str, unsigned int *i)
{
	int	j;

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
	j = 0;
	while (redir_str[j] == redir_str[0] && j < 2)
		j++;
	return (log_msg(ERROR, MSG_SYNTAX_ERR_NEAR, redir_str[j]), NOTDEF);
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
	skip_until(line, i, WHITESPACE, false);
	lex_len = arg_len(&line[*i]);
	if (lex_len == 0)
		return (free(token), log_msg(ERROR, MSG_SYNTAX_ERR_NEAR, line[*i]),
			NULL);
	token->value = ft_substr(line, *i, lex_len);
	if (!(token->value))
		return (free(token), NULL);
	if (token->type == R_HEREDOC && (ft_strchr(token->value, '\'')
			|| ft_strchr(token->value, '"')))
		token->type = R_QUOTEDOC;
	*i += lex_len;
	return (token);
}
