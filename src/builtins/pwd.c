/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:17:44 by hrother           #+#    #+#             */
/*   Updated: 2024/03/25 00:25:32 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(const t_cmd *cmd, t_list **envp)
{
	char	*pwd;

	(void)envp;
	log_msg(DEBUG, "executing builtin_pwd");
	// TODO: consider using own envp list instead of getcwd
	pwd = getcwd(NULL, 0); // TODO: consider setting a max size
	if (pwd == NULL)
	{
		log_msg(ERROR, "pwd: %s", strerror(errno));
		return (FAILURE);
	}
	ft_putendl_fd(pwd, cmd->fd_out);
	free(pwd);
	return (SUCCESS);
}
