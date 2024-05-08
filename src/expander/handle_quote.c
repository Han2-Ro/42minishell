/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:59:26 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/08 13:09:08 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

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

int	handle_quote(unsigned int i, char **str, int *quote)
{
	int		new_quote;
	char	*temp;
	int		increment_by;

	new_quote = get_quote(*quote, (*str)[i]);
	increment_by = 1;
	// if (new_quote == -1)
	// 	log_msg(ERROR, "Quote Error");
	if (*quote != new_quote)
	{
		temp = *str;
		*str = str_insert("", (*str), i, i + 1);
		free(temp);
		increment_by = 0;
	}
	*quote = new_quote;
	return (increment_by);
}
