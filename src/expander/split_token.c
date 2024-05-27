/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:53:14 by hrother           #+#    #+#             */
/*   Updated: 2024/05/27 17:05:24 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_list	*split_token(char *str, int *i, int to)
{
	t_list	*list;
	int		from;

	list = NULL;
	from = 0;
	while (str[*i] && *i < to)
	{
		if (ft_strchr(WHITESPACE, str[*i]) != NULL)
		{
			if (*i > 0)
				seperate_token(&list, str, from, *i);
			while (str[*i] && ft_strchr(WHITESPACE, str[*i]))
				(*i)++;
			from = *i;
		}
		else
			(*i)++;
	}
	if (*i < (int)ft_strlen(str) || from < *i)
		seperate_token(&list, str, from, ft_strlen(str));
	*i -= from;
	return (list);
}
