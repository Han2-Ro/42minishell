/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:59:26 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/26 15:29:42 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

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

int	add_token(t_list **token_lst, const char *line, unsigned int *i, t_token *(*lex)(const char *, unsigned int *))
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

t_list	*lexer(const char *line)
{
	unsigned int	line_len;
	unsigned int	i;
	bool			capture_args;
	t_list			*token_lst;
	int				fail;
	
	token_lst = NULL;
	line_len = ft_strlen(line);
	i = 0;
	fail = 0;
	capture_args = false;
	while (i < line_len && !fail)
	{
		skip_until(line, &i, " ", false);
		if (!line[i])
			break ;
		if (line[i] == '|')
		{
			fail += add_token(&token_lst, line, &i, lex_pipe);
			capture_args = false;
		}
		else if (ft_strchr("<>", line[i]))
		{
			fail += add_token(&token_lst, line, &i, lex_redirect);
		}
		else if (capture_args)
		{
			fail += add_token(&token_lst, line, &i, lex_arg);
		}
		else
		{
			fail += add_token(&token_lst, line, &i, lex_cmd);
			capture_args = true;
		}
	}
	ft_lstiter(token_lst, expand);
	return (token_lst);
}
