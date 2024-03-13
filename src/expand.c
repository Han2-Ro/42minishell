/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:59:26 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/13 17:51:18 by aprevrha         ###   ########.fr       */
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

char	*str_insert(char const *i_str, char *o_str, unsigned int from,
		unsigned int to)
{
	unsigned int	len_total;
	unsigned int	len_o;
	unsigned int	len_i;
	char			*result;

	if (i_str == NULL)
		return (ft_strdup(o_str));
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
/*
 * @brief Expands $arg and $? where arg is an environment var
 *
 */
void	expand_var(unsigned int *i, char *str[1])
{
	unsigned int	var_i;
	char			*temp;
	char			*env_val;

	var_i = *i;
	(*i)++;
	skip_until(*str, i, " $\'\"", true);
	temp = ft_substr(*str, var_i + 1, *i - var_i - 1);
	env_val = getenv(temp);
	if (!env_val)
		env_val = "";
	free(temp);
	temp = str_insert(env_val, *str, var_i, *i);
	free(*str);
	*str = temp;
	*i = var_i + ft_strlen(env_val);
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

void	handle_quote(unsigned int *i, char *str[1], int *quote)
{
	int		new_quote;
	char	*temp;

	new_quote = get_quote(*quote, (*str)[*i]);
	if (new_quote == -1)
		log_msg(ERROR, "Quote Error");
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

void	expand(void *token)
{
	unsigned int	i;
	char			*str;
	int				quote;

	if (((t_token *)token)->type == PIPE)
		return ;
	str = ((t_token *)token)->value;
	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		skip_until(str, &i, "$'\"", true);
		if (str[i] == '\0')
			break ;
		else if (ft_strchr("'\"", str[i]))
			handle_quote(&i, &str, &quote);
		else if (str[i] == '$' && quote == 1)
			i++;
		else if (str[i] == '$')
			expand_var(&i, &str);
	}
	if (quote != 0)
		log_msg(WARNING, "Syntax Error: Quote not correctly closed!");
	((t_token *)token)->value = str;
}
