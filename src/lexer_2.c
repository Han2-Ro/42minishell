/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:46:13 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/07 13:00:18 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*lex_cmd(const char *line, unsigned int *i)
{
	t_token			*token;
	unsigned int	lex_len;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	lex_len = 0;
	skip_until(&line[*i], &lex_len, WHITESPACE "|<>", true);
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
	return (log_msg(ERROR, "Wrong redirect syntax!"), NOTDEF);
	skip_until(redir_str, i, "<>", false);
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
	token->value = ft_substr(line, *i, lex_len);
	if (!(token->value))
		return (free(token), NULL);
	if (token->type == R_HEREDOC && (ft_strchr(token->value, '\'')
			|| ft_strchr(token->value, '"')))
		token->type = R_QUOTEDOC;
	*i += lex_len;
	return (token);
}
