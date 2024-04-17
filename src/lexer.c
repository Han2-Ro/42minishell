/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:59:26 by aprevrha          #+#    #+#             */
/*   Updated: 2024/04/17 22:28:57 by aprevrha         ###   ########.fr       */
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

t_token	*lex_part(const char *line, unsigned int *i)
{
	t_token			*token;
	unsigned int	lex_len;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	lex_len = 0;
	skip_until(&line[*i], &lex_len, "|<>", true);
	token->type = PART;
	token->value = ft_substr(line, *i, lex_len);
	if (!(token->value))
		return (free(token), NULL);
	*i += lex_len;
	return (token);
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
	t_list			*token_lst;
	int				fail;
	
	token_lst = NULL;
	line_len = ft_strlen(line);
	i = 0;
	fail = 0;
	while (i < line_len && !fail)
	{
		skip_until(line, &i, " ", false);
		if (!line[i])
			break ;
		if (line[i] == '|')
			fail += add_token(&token_lst, line, &i, lex_pipe);
		else if (ft_strchr("<>", line[i]))
			fail += add_token(&token_lst, line, &i, lex_redirect);
		else
			fail += add_token(&token_lst, line, &i, lex_part);
	}
	return (token_lst);
}

t_list *relex(char *str, bool cmd)
{
	t_list *token_lst;
	unsigned int i;

	i = 0;
	token_lst = NULL;
	
	while (str[i])
	{
		skip_until(str, &i, " ", false);
		if (token_lst == NULL && cmd)
		{
			add_token(&token_lst, str, &i, lex_cmd);
			cmd = false;
		}
		else
			add_token(&token_lst, str, &i, lex_arg);
	}
	return (token_lst);
}

int lex_split(t_list **token_lst)
{
	t_list *curr;
	t_list *next;
	t_list *new;
	bool	cmd;

	curr = *token_lst;
	cmd = true;
	while (curr)
	{
		ft_lstiter(*token_lst, print_token_new);
		
		if (((t_token *)(curr->content))->type == PIPE)
			cmd = true;
		if (((t_token *)(curr->content))->type == PART)
		{
			next = curr->next;
			new = relex(((t_token *)(curr->content))->value, cmd);
			ft_lstinsert(curr, new);
			ft_lstrmvone(token_lst, curr, free_token);
			cmd = false;
			curr = next;
		}
		else
			curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
