/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:41:35 by hrother           #+#    #+#             */
/*   Updated: 2024/04/22 13:02:54 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	return(ft_strncmp(s1, s2, ft_strlen(s2) + 1));
}

t_cmd	*new_cmd(char *bin, char **args)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (log_msg(ERROR, "malloc failed"), NULL);
	cmd->bin = bin;
	cmd->args = args;
	cmd->redirects = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->pid = -1;
	cmd->status = 0;
	return (cmd);
}

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	ft_lstclear(&cmd->redirects, pass);
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

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/**
 * @brief This function does nothing: Useful for ft_lstclear
 */
void	pass(void *content)
{
	(void)content;
}
