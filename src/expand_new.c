/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:49:00 by hrother           #+#    #+#             */
/*   Updated: 2024/05/05 13:02:50 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_status(char *str, int i, const int status, int *expand_len)
{
	char	*status_str;
	char	*new_str;

	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	*expand_len = ft_strlen(status_str);
	new_str = str_insert(status_str, str, i, i + 2);
	free(status_str);
	return (new_str);
}

char	*expand_var_new(char *str, int i, const t_list *env_list,
		int *expand_len)
{
	char	*new_str;
	char	*env_key;
	char	*env_val;
	int		j;

	j = i + 1;
	while (ft_strchr(SPECIAL_CHARS WHITESPACE, str[j]) == NULL)
		j++;
	env_key = ft_substr(str, i + 1, j - i - 1);
	env_val = ft_getenv(env_list, env_key);
	free(env_key);
	if (!env_val)
		env_val = "";
	*expand_len = ft_strlen(env_val);
	new_str = str_insert(env_val, str, i, j);
	return (new_str);
}

int	replace_dollar(char **str, int i, const t_evars evars)
{
	char	*new_value;
	int		expand_len;

	log_msg(DEBUG, "replace_dollar: '%s' at %i", *str, i);
	expand_len = 1;
	if (ft_strchr(WHITESPACE, (*str)[i + 1]) != NULL)
		return (1);
	else if ((*str)[i + 1] == '?')
		new_value = expand_status(*str, i, evars.status, &expand_len);
	else
		new_value = expand_var_new(*str, i, evars.envp, &expand_len);
	free(*str);
	*str = new_value;
	if (!new_value)
		return (FAILURE);
	return (expand_len);
}

t_list	*split_token_here(t_list *list, int *i)
{
	t_token	*token;
	char	*str;
	t_list	*next;

	next = list->next;
	token = (t_token *)list->content;
	str = token->value;
	token->value = ft_substr(str, 0, *i);
	while (str[*i] && ft_strchr(WHITESPACE, str[*i]) != NULL)
		(*i)++;
	if (str[*i] == '\0')
		return (free(str), list);
	token = malloc(sizeof(t_token));
	if (!token)
		return (free(str), NULL);
	token->type = ARG;
	token->value = ft_substr(str, *i, ft_strlen(str) - *i);
	// substr malloc prot
	free(str);
	list->next = ft_lstnew(token);
	// lstnew malloc prot
	list = list->next;
	list->next = next;
	return (list);
}

int	seperate_token(t_list **list, char *str, int from, int to)
{
	t_token	*token;
	t_list	*new;

	token = new_token(ARG, ft_substr(str, from, to - from));
	if (!token || !token->value)
		return (free(token), FAILURE);
	new = ft_lstnew(token);
	if (!new)
		return (free_token(token), FAILURE);
	ft_lstadd_back(list, new);
	return (SUCCESS);
}

t_list	*split_token(char *str, int from, int to)
{
	t_list	*list;
	int		i;

	list = NULL;
	i = from;
	from = 0;
	while (str[i] && i < to)
	{
		if (ft_strchr(WHITESPACE, str[i]) != NULL)
		{
			if (i > 0)
				seperate_token(&list, str, from, to);
			while (str[i] && ft_strchr(WHITESPACE, str[i]))
				i++;
			from = i;
		}
		i++;
	}
	if (from != i)
		seperate_token(&list, str, from, to);
	return (list);
}

t_list	*handle_dollar(t_list *list, int *i, const t_evars evars,
		const int quote)
{
	t_token	*token;
	int		len;
	t_list	*new;

	token = (t_token *)list->content;
	len = replace_dollar(&token->value, *i, evars);
	if (quote != 0 || len < 2 || (token->type != CMD && token->type != ARG))
		return (*i += len, list);
	new = split_token(token->value, *i, *i + len);
	ft_lstrmvone(&list, list, free_token);
	if (new == NULL)
		return (list);
	ft_lstlast(new)->next = list;
	return (new);
}

/**
 * @brief Expands the token in the list.
 * @return quote status at end of string or -1 on error.
 */
int	expand_token(t_list **list, const t_evars evars)
{
	t_token	*token;
	int		quote;
	int		i;

	i = 0;
	quote = 0;
	token = (t_token *)(*list)->content;
	while (token->value[i] != '\0')
	{
		if (ft_strchr("\"\'", token->value[i]) != NULL)
			i += handle_quote(i, &token->value, &quote);
		else if (token->value[i] == '$' && quote != 1
			&& token->type != R_HEREDOC && token->type != R_QUOTEDOC)
		{
			*list = handle_dollar(*list, &i, evars, quote);
			if (*list != NULL)
				token = (t_token *)(*list)->content;
		}
		else
			i++;
		if (*list == NULL || token->value == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	expand_heredoc(char **str, t_evars evars)
{
	unsigned int	i;
	int				expand_len;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '$')
		{
			expand_len = replace_dollar(str, i, evars);
			i += expand_len;
		}
		else
			i++;
	}
	return (SUCCESS);
}

int	expand_token_list(t_list *token_lst, const t_evars evars)
{
	t_list	*current;
	t_token	*token;
	int		quote;
	int		ret;

	ret = SUCCESS;
	current = token_lst;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type != PIPE)
		{
			quote = expand_token(&current, evars);
			if (quote > 0)
				log_msg(ERROR, "Syntax Error: Quote not closed");
			ret |= quote;
		}
		if (current != NULL)
			current = current->next;
	}
	return (ret);
}
