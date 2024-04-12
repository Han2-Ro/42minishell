/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:59:26 by aprevrha          #+#    #+#             */
/*   Updated: 2024/04/12 15:48:47 by aprevrha         ###   ########.fr       */
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
char	*get_var(char *str, unsigned int *i, t_list *envp, int status)
{
	unsigned int	var_i;
	char			*env_key;
	char			*env_val;
	
	var_i = i;
	if (str[*i] == '?')
	{
		env_val = ft_itoa(status);
		if (!env_val)
			return (NULL);
		*i += 1;
	}
	else 
	{
		skip_until(*str, i, " $\'\"", true);
		env_key = ft_substr(*str, var_i + 1, *i - var_i - 1);
		if (!env_key)
			return (NULL);
		env_val = ft_getenv(envp, env_key);
		if (!env_val)
			env_val = (char *)malloc(sizeof(char) * 1)
		free(env_key);
	}
	if (!env)
}

/**
 * @brief Expands $arg and $? where arg is an environment var
 * @brief Exxpects to be at the start or a var "$"
 */
char	*expand_var(unsigned int *i, char *str[1], t_list *envp, int status)
{
	unsigned int	var_i;
	char			*temp;
	char			*env_val;

	var_i = *i;

	if (!env_val)
		temp = str_insert("", *str, var_i, *i);
	else
		temp = str_insert(env_val, *str, var_i, *i);
	free (env_val);
	*i = var_i + ft_strlen(env_val);
	return (temp);
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

int	expand(t_token *token, t_list *envp, int status)
{
	unsigned int	i;
	char			*str;
	int				quote;
	char			*temp;

	if (token->type == PIPE)
		return ;
	str = token->value;
	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		skip_until(str, &i, "$\'\"", true);
		if (str[i] == '\0')
			break ;
		else if (ft_strchr("'\"", str[i]))
			handle_quote(&i, &str, &quote);
		else if (str[i] == '$' && quote == 1)
			i++;
		else if (str[i] == '$')
		{
			temp = expand_var(&i, &str, envp, status);
			if (!temp)
				return (1);
		}
	}
	if (quote != 0)
		log_msg(WARNING, "Syntax Error: Quote not correctly closed!");
	((t_token *)token)->value = str;
}

void	expand_tokens(t_list *token_lst, t_list *envp, int status)
{
	while (token_lst)
	{
		expand((t_token *)token_lst->content, envp, status);
		token_lst = token_lst->next;
	}
}
