/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:59:26 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/08 16:36:00 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

// TODO: Clear the list logic
void	free_tokenlst(t_list *tokenlst)
{
	log_msg(WARNING, "lexer had to clear token list, something went wrong...");
}

static void	skip_until(const char *str, int *i, const char *charset, bool val)
{
	while ((ft_strchr(charset, str[*i]) != 0) != val && str[*i] != '\0')
		*i++;
}

t_token	*lex_cmd(const char *line, int *i)
{
	t_token			*token;
	unsigned int	lex_len;

	(t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	lex_len = 0;
	skip_until(line[*i], &lex_len, " ", true);
	token->type = CMD;
	token->value = ft_substr(line, i, lex_len);
	if (!(token->value))
		return (free(token), NULL);
	i += lex_len;
	return (token);
}

static unsigned int	arg_len(const char *arg)
{
	unsigned int	len;

	len = 0;
	if (arg[0] == '\'')
	{
		skip_until(&arg[1], &len, "\'", true);
		len += 2;
	}
	else if (arg[0] == '\"')
	{
		skip_until(&arg[1], &len, "\"", true);
		len += 2;
	}
	else
	{
		skip_until(&arg[0], &len, " ", true);
	}
}

t_token	*lex_arg(const char *line, unsigned int *i)
{
	t_token			*token;
	unsigned int	lex_len;

	(t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	lex_len = 0;
	lex_len = arg_len(&line[*i]);
	token->type = ARG;
	token->value = ft_substr(line, i, lex_len);
	if (!(token->value))
		return (free(token), NULL);
	i += lex_len;
	return (token);
}

t_token_type	redirect_type(char *redir_str)
{
	t_token_type	redir_type;

	if (redir_str[0] == '>' && redir_str[1] == '>' && !ft_strchr("<>",
			redir_str[2]))
		redir_type = R_APPEND;
	else if (redir_str[0] == '>' && !ft_strchr("<>", redir_str[1]))
		redir_type = R_OUT;
	else if (redir_str[0] == '<' && redir_str[1] == '<' && !ft_strchr("<>",
			redir_str[2]))
		redir_type = R_HEREDOC;
	else if (redir_str[0] == '<' && !ft_strchr("<>", redir_str[1]))
		redir_type = R_IN;
	else
		return (log_msg(ERROR, "Wrong redirect syntax!"), NULL);
	return (redir_type);
}

t_token	*lex_redirect(const char *line, int *i)
{
	t_token			*token;
	unsigned int	lex_len;
	t_token_type	redir_type;

	(t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	lex_len = 0;
	redir_type = redirect_type(&line[*i]);
	if (!redir_type)
		return (free(token), NULL);
	token->type = redir_type;
	skip_until(line[*i], i, "<>", false);
	skip_until(line[*i], i, " ", false);
	skip_until(line[*i], &lex_len, " ", true);
	token->value = ft_substr(line, i, lex_len);
	if (!(token->value))
		return (free(token), NULL);
	i += lex_len;
	return (token);
}

t_token	*lex_pipe(const char *line, int *i)
{
	t_token	*token;

	(t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = PIPE;
	token->value = NULL;
	*i++;
	return (token);
}

void	lstadvance_head(t_list *head)
{
	t_list	*next;

	next = head->next;
	free(head);
	head = next;
}

// TODO: Handle error: "lex retured NULL"
// TODO: Fix bugs
t_list	*lexer(const char *line)
{
	unsigned int	line_len;
	unsigned int	i;
	bool			capture_args;
	t_list			*token_lst;

	line_len = ft_strlen(line);
	i = 0;
	capture_args = false;
	token_lst = ft_lstnew(NULL);
	while (i < line_len)
	{
		skip_until(line, &i, " ", false);
		if (line[i] == '|')
		{
			ft_lstadd_back(token_lst, ft_lstnew(lex_pipe(&line, &i)));
			capture_args = false;
		}
		else if (ft_strchr("<>", line[i]))
			ft_lstadd_back(token_lst, ft_lstnew(lex_redirect(&line, &i)));
		else if (capture_args)
			ft_lstadd_back(token_lst, ft_lstnew(lex_arg(&line, &i)));
		else
		{
			ft_lstadd_back(token_lst, ft_lstnew(lex_cmd(&line, &i)));
			capture_args = true;
		}
	}
	return (lstadvance_head(token_lst), token_lst);
}
