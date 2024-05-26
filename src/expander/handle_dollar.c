/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:55:50 by hrother           #+#    #+#             */
/*   Updated: 2024/05/26 18:33:21 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

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

char	*expand_var(char *str, int i, const t_list *env_list, int *expand_len)
{
	char	*new_str;
	char	*env_key;
	char	*env_val;
	int		j;

	j = i + 1;
	while (isalnum(str[j]) || str[j] == '_')
		j++;
	env_key = ft_substr(str, i + 1, j - i - 1);
	env_val = get_envvalue(env_list, env_key);
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
		new_value = expand_var(*str, i, evars.envl, &expand_len);
	free(*str);
	*str = new_value;
	if (!new_value)
		return (FAILURE);
	return (expand_len);
}

void	handle_dollar(t_list ***list, int *i, const t_evars evars,
		const int quote)
{
	t_token	*token;
	int		len;
	t_list	*new;
	t_list	*next;

	token = (t_token *)(**list)->content;
	len = replace_dollar(&token->value, *i, evars);
	if (quote != 0 || len < 0 || (token->type != CMD && token->type != ARG))
	{
		*i += len;
		return ;
	}
	new = split_token(token->value, i, *i + len);
	next = (**list)->next;
	if (new != NULL)
		(**list)->next = new;
	ft_lstrmvone(*list, **list, free_token);
	if (new == NULL)
		return ;
	while (ft_lstsize(**list) > 1)
		*list = &(**list)->next;
	(**list)->next = next;
}
