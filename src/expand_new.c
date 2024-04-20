/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:49:00 by hrother           #+#    #+#             */
/*   Updated: 2024/04/20 13:38:40 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_status(char *str, int i, int status)
{
	char	*status_str;
	char	*new_str;

	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	new_str = str_insert(status_str, str, i, i + 2);
	free(status_str);
	return (new_str);
}

char	*expand_var_new(char *str, int i, t_list *env_list)
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
		env_val = ft_strdup("");
	new_str = str_insert(env_val, str, i, j);
	return (new_str);
}

int	handle_dollar(char **str, int i, t_list *env_list, int status)
{
	char	*new_value;

	log_msg(DEBUG, "handle_dollar: '%s' at %i", *str, i);
	if ((*str)[i + 1] == '?')
		new_value = expand_status(*str, i, status);
	else
		new_value = expand_var_new(*str, i, env_list);
	free (*str);
	if (!new_value)
		return (EXIT_FAILURE);
	*str = new_value;
	return (EXIT_SUCCESS);
}

int	expand_token(t_list *list, t_list *env_list, int status)
{
	t_token			*token;
	int				quote;
	unsigned int	i;

	print_token_new(list->content);
	i = 0;
	quote = 0;
	token = (t_token *)list->content;
	while (token->value[i] != '\0')
	{
		if (ft_strchr("\"\'", token->value[i]) != NULL)
			handle_quote(&i, &token->value, &quote);
		else if (token->value[i] == '$' && quote != 1)
		{
			handle_dollar(&token->value, i, env_list, status);
			// split_token(list, new_value, i);
		}
		else
			i++;
		if (token->value == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	expand_tokens_new(t_list *token_lst, t_list *env_list, int status)
{
	t_list *current;
	t_token *token;

	current = token_lst;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type != PIPE && token->type != R_HEREDOC)
		{
			expand_token(current, env_list, status);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}