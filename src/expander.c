/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:49:00 by hrother           #+#    #+#             */
/*   Updated: 2024/05/08 13:01:02 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/**
 * @brief Expands the token in the list.
 * @return quote status at end of string or -1 on error.
 */
int	expand_token(t_list ***list, const t_evars evars)
{
	t_token	*token;
	int		quote;
	int		i;

	i = 0;
	quote = 0;
	token = (t_token *)(**list)->content;
	while (token->value[i] != '\0')
	{
		if (ft_strchr("\"\'", token->value[i]) != NULL)
			i += handle_quote(i, &token->value, &quote);
		else if (token->value[i] == '$' && quote != 1
			&& token->type != R_HEREDOC && token->type != R_QUOTEDOC)
		{
			handle_dollar(list, &i, evars, quote);
			if (**list != NULL)
				token = (t_token *)(**list)->content;
		}
		else
			i++;
		if (*list == NULL || **list == NULL || token->value == NULL)
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

int	expand_token_list(t_list **token_lst, const t_evars evars)
{
	t_list	**current;
	t_token	*token;
	int		quote;
	int		ret;

	ret = SUCCESS;
	current = token_lst;
	while (*current)
	{
		token = (t_token *)(*current)->content;
		if (token->type != PIPE)
		{
			quote = expand_token(&current, evars);
			if (quote > 0)
				log_msg(ERROR, "Syntax Error: Quote not closed");
			ret |= quote;
		}
		if (*current != NULL)
			current = &(*current)->next;
	}
	return (ret);
}
