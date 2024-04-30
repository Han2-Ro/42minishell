/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:06:11 by hrother           #+#    #+#             */
/*   Updated: 2024/04/30 18:03:22 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		str = get_next_line(STDIN_FILENO);
		while (str != NULL)
		{
			log_msg(DEBUG, "gnl: %s", str);
			free(str);
			str = get_next_line(STDIN_FILENO);
		}
	}
	return (exit_status);
}
