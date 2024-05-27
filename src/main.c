/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:06:11 by hrother           #+#    #+#             */
/*   Updated: 2024/05/27 21:27:30 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		exit_status;
	t_evars	evars;

	(void)argc;
	(void)argv;
	evars.status = 0;
	evars.tty = isatty(STDIN_FILENO);
	evars.is_child = false;
	if (evars.tty == -1)
		return (1);
	evars.envl = envp_to_list(envp);
	if (!evars.envl)
		return (1);
	exit_status = shell_loop(&evars);
	ft_lstclear(&evars.envl, free_env);
	if (evars.tty && !evars.is_child)
		ft_putendl_fd("exit", STDERR_FILENO);
	return (exit_status);
}
