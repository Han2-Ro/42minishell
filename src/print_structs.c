/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:12:46 by hrother           #+#    #+#             */
/*   Updated: 2024/03/07 16:27:22 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void	print_cmd(t_cmd *cmd)
{
	int	i;

	printf("cmd: %s\n", cmd->bin);
	printf("pid: %d\n", cmd->pid);
	printf("args:\n");
	i = 0;
	while (cmd->args[i] != NULL)
	{
		printf("  %s\n", cmd->args[i]);
		i++;
	}
	/*
	printf("envp:\n");
	i = 0;
	while (cmd->envp[i] != NULL)
	{
		printf("  %s\n", cmd->envp[i]);
		i++;
	}
	*/
}

void	print_list(t_list *lst)
{
	while (lst != NULL)
	{
		print_cmd((t_cmd *)lst->content);
		lst = lst->next;
	}
}