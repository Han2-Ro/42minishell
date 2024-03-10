/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:59:26 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/10 23:33:06 by aprevrha         ###   ########.fr       */
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
void	expand(void *token)
{
	unsigned int	i;
	char			*str;
	char			*temp;
	unsigned int	var_i;
	char			*env_val;

	str = ((t_token *)token)->value;
	i = 0;
	while (str[i] != '\0')
	{
		skip_until(str, &i, "$", true);
		if (str[i] == '\0')
			break ;
		var_i = i;
		i++;
		skip_until(str, &i, " $\'\"", true);
		temp = ft_substr(str, var_i + 1, i - var_i);
		env_val = getenv(temp);
		if (!env_val)
			env_val = "";
		free(temp);
		temp = str_insert(env_val, str, var_i, i);
		free(str);
		str = temp;
		i = var_i + ft_strlen(env_val);
	}
	((t_token *)token)->value = str;
}
