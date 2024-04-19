/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:49:00 by hrother           #+#    #+#             */
/*   Updated: 2024/04/19 16:49:15 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_dollar(char *str, int i, t_list *env_list, int status)
{
	char	*new_str;
	char	*env_val;

	if (str[i + 1] == '?')
	{
		env_val = ft_itoa(status);
		if (!env_val)
			return (NULL);
		new_str = str_insert(env_val, str, i, i + 1);
	}
    else
    {
        int j = i + 1;
        while (str[j] && str[j] != ' ' )
    }
}

int	expand_token(t_list *list, t_list *env_list, int status)
{
	t_token	*token;
	int		quote;
	int		i;

	token = (t_token *)list->content;
	while (token->value[i] != '\0')
	{
		if (ft_strchr("\"\'", token->value[i]) != NULL)
			handle_quote(&i, &token->value, &quote);
		else if (token->value[i] == '$' && quote != 1)
		{
			handle_dollar();
		}
		i++;
	}
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
}