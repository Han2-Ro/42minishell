/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:06:11 by hrother           #+#    #+#             */
/*   Updated: 2024/04/29 14:00:12 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char const *argv[], char *envp[])
{
	t_list	*envp_lst;
	int		exit_status;
	char	*str;

	str = NULL;
	(void)argc;
	(void)argv;
	envp_lst = envp_to_list(envp);
	if (!envp_lst)
		return (FAILURE);
	exit_status = shell_loop(envp_lst);
	ft_lstclear(&envp_lst, free_env);
	if (!isatty(STDIN_FILENO))
	{
		log_msg(DEBUG, "running gnl until it is NULL");
		while (str != NULL)
		{
			str = get_next_line(STDIN_FILENO);
			free(str);
		}
	}
	return (exit_status);
}
