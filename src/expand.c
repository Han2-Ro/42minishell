/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:59:26 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/07 12:54:21 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

/**
 * @brief Inserts a string into an existing string
 * @param i_str The string to be inserted
 * @param o_str The original string
 * @param from Index from where to start replacing the original string
 * @param to Index to where to replace the original string
 * @return The resulting string
 */
char	*str_insert(char const *i_str, char *o_str, unsigned int from,
		unsigned int to)
{
	unsigned int	len_total;
	unsigned int	len_o;
	unsigned int	len_i;
	char			*result;

	if (i_str == NULL || o_str == NULL)
		return (NULL);
	len_i = ft_strlen(i_str);
	len_o = ft_strlen(o_str);
	len_total = from + len_i + len_o - to + 1;
	result = (char *)malloc(sizeof(char) * len_total);
	if (!result)
		return (NULL);
	ft_strlcpy(result, o_str, from + 1);
	ft_strlcat(result, i_str, len_total);
	ft_strlcat(result, o_str + to, len_total);
	return (result);
}

// Fuck the 25 line limit :)
char	*expand_var_2(t_expand_info *ex, char *env_val, bool pls_free)
{
	int		val_len;
	char	*temp;

	if (!env_val)
	{
		temp = str_insert("", ex->str, ex->var_idx, ex->i);
		val_len = 0;
	}
	else
	{
		temp = str_insert(env_val, ex->str, ex->var_idx, ex->i);
		val_len = ft_strlen(env_val);
	}
	if (pls_free)
		free(env_val);
	ex->i = ex->var_idx + val_len;
	return (temp);
}

/**
 * @brief Expands $arg and $? where arg is an environment var
 * @brief Expects to be behind "$" at the start or a var
 */
char	*expand_var(t_expand_info *ex)
{
	char	*env_val;
	char	*env_key;
	bool	pls_free;

	pls_free = false;
	ex->var_idx = ex->i;
	(ex->i) += 1;
	if (ex->str[ex->i] == '?')
	{
		env_val = ft_itoa(ex->status);
		if (!env_val)
			return (NULL);
		ex->i += 1;
		pls_free = true;
	}
	else
	{
		skip_until(ex->str, &(ex->i), " $\'\"", true);
		env_key = ft_substr(ex->str, ex->var_idx + 1, ex->i - ex->var_idx - 1);
		if (!env_key)
			return (NULL);
		env_val = ft_getenv(ex->envp, env_key);
		free(env_key);
	}
	return (expand_var_2(ex, env_val, pls_free));
}

int	get_quote(int quote, const char c)
{
	if (quote == 0)
	{
		if (c == '\'')
			return (1);
		if (c == '"')
			return (2);
	}
	else if (quote == 1)
	{
		if (c == '\'')
			return (0);
		if (c == '"')
			return (1);
	}
	else if (quote == 2)
	{
		if (c == '\'')
			return (2);
		if (c == '"')
			return (0);
	}
	return (-1);
}

void	handle_quote(unsigned int *i, char **str, int *quote)
{
	int		new_quote;
	char	*temp;

	new_quote = get_quote(*quote, (*str)[*i]);
	// if (new_quote == -1)
	// 	log_msg(ERROR, "Quote Error");
	if (*quote != new_quote)
	{
		temp = *str;
		*str = str_insert("", (*str), *i, *i + 1);
		free(temp);
	}
	else
		(*i)++;
	*quote = new_quote;
}
/*
int	expand_loop(t_expand_info *ex)
{
	char	*temp;

	skip_until(ex->str, &ex->i, "$\'\"", true);
	if (ex->str[ex->i] == '\0')
		return (EXIT_SUCCESS);
	else if (ft_strchr("'\"", ex->str[ex->i]))
		handle_quote(&ex->i, &ex->str, &ex->quote);
	else if (ex->str[ex->i] == '$' && ex->quote == 1)
		(ex->i)++;
	else if (ex->str[ex->i] == '$')
	{
		temp = expand_var(ex);
		free(ex->str);
		if (!temp)
			return (EXIT_FAILURE);
		ex->str = temp;
	}
	return (EXIT_SUCCESS);
}

char	*expand(char *string, t_list *envp, int status)
{
	t_expand_info	ex;

	ex.str = ft_strdup(string);
	if (!ex.str)
		return (NULL);
	ex.i = 0;
	ex.quote = 0;
	ex.envp = envp;
	ex.status = status;
	while (ex.str[ex.i] != '\0')
	{
		if (expand_loop(&ex))
		{
			free(ex.str);
			return (NULL);
		}
	}
	// if (ex.quote != 0)
	// 	log_msg(WARNING, "Syntax Error: Quote not correctly closed!");
	return (ex.str);
}

int	expand_tokens(t_list *token_lst, t_list *envp, int status)
{
	char	*temp;

	while (token_lst)
	{
		if (((t_token *)(token_lst->content))->type != PIPE)
		{
			temp = expand(((t_token *)(token_lst->content))->value, envp,
					status);
			if (!temp)
				return (EXIT_FAILURE);
			free(((t_token *)(token_lst->content))->value);
			((t_token *)(token_lst->content))->value = temp;
		}
		token_lst = token_lst->next;
	}
	return (EXIT_SUCCESS);
}
*/