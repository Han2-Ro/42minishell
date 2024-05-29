/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:17:44 by hrother           #+#    #+#             */
/*   Updated: 2024/05/29 11:39:09 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(const t_cmd *cmd)
{
	char	*cwd;

	log_msg(DEBUG, "executing builtin_pwd");
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		log_msg(ERROR, "pwd: %s", strerror(errno));
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(cwd, cmd->fd_out);
	free(cwd);
	return (EXIT_SUCCESS);
}
