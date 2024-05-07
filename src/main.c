/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:06:11 by hrother           #+#    #+#             */
/*   Updated: 2024/05/07 12:34:55 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_gnl_buf(void)
{
	char	*str;

	str = NULL;
	log_msg(DEBUG, "running gnl until it is NULL");
	str = get_next_line(STDIN_FILENO);
	while (str != NULL)
	{
		log_msg(DEBUG, "gnl: %s", str);
		free(str);
		str = get_next_line(STDIN_FILENO);
	}
}

int	main(int argc, char const *argv[], char *envp[])
{
	t_list	*envp_lst;
	int		exit_status;
	int		tty;

	(void)argc;
	(void)argv;
	tty = isatty(STDIN_FILENO);
	if (tty == -1)
		return (1);
	envp_lst = envp_to_list(envp);
	if (!envp_lst)
		return (FAILURE);
	exit_status = shell_loop(envp_lst, tty);
	ft_lstclear(&envp_lst, free_env);
	if (!tty)
		clear_gnl_buf();
	return (exit_status);
}
