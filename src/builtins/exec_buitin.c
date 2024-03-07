/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buitin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:36:34 by hrother           #+#    #+#             */
/*   Updated: 2024/03/06 19:37:24 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_builtin(const t_cmd cmd)
{
	if (ft_strncmp(cmd.bin, "pwd", 5) == 0)
		exit(builtin_pwd());
	return (SUCCESS);
}
