/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:17:44 by hrother           #+#    #+#             */
/*   Updated: 2024/03/06 19:29:00 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

	log_msg(DEBUG, "executing builtin_pwd");
	// TODO: consider using own envp list instead of getcwd
	pwd = getcwd(NULL, 0); // TODO: consider setting a max size
	if (pwd == NULL)
	{
		log_msg(ERROR, "pwd: %s", strerror(errno));
		return (FAILURE);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (SUCCESS);
}
