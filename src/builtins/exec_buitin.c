/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buitin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:36:34 by hrother           #+#    #+#             */
/*   Updated: 2024/03/15 16:04:13 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_builtin(const t_cmd cmd, t_list **envp)
{
	if (ft_strncmp(cmd.bin, "pwd", 5) == 0)
		exit(builtin_pwd());
	if (ft_strncmp(cmd.bin, "env", 5) == 0)
		exit(builtin_env(*envp));
	if (ft_strncmp(cmd.bin, "export", 10) == 0)
		exit(builtin_export(envp, cmd.args));
	return (SUCCESS);
}
