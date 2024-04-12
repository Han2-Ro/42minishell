/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:06:11 by hrother           #+#    #+#             */
/*   Updated: 2024/04/12 16:08:44 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_list	*envp_lst;
	int		exit_status;

	(void)argc;
	(void)argv;
	envp_lst = envp_to_list(envp);
	if (!envp_lst)
		return (FAILURE);
	exit_status = shell_loop(envp_lst);
	ft_lstclear(&envp_lst, free_env);
	return (exit_status);
}
