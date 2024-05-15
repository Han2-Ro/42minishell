/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:41:35 by hrother           #+#    #+#             */
/*   Updated: 2024/05/15 21:03:11 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}

/**
 * @brief This function does nothing: Useful for ft_lstclear
 */
void	pass(void *content)
{
	(void)content;
}

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	ft_lstclear(&cmd->redirects, pass);
	free(cmd->bin);
	free(cmd->args);
	free(cmd);
}

void	free_str_arr(char **strs, int size)
{
	while (size > 0)
	{
		free(strs[size - 1]);
		size--;
	}
	free(strs);
}

void	free_nullterm_str_arr(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
