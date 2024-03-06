/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:17:44 by hrother           #+#    #+#             */
/*   Updated: 2024/03/06 18:24:54 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

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
