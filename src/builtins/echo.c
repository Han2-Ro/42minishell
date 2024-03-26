/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:47:08 by hannes            #+#    #+#             */
/*   Updated: 2024/03/26 12:05:22 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_echo(const t_cmd *cmd, t_list **envp)
{
	bool	n_flag;
	int		i;

	(void)envp;
	i = 1;
	while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 5) == 0)
		i++;
	n_flag = (i > 1);
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
}
