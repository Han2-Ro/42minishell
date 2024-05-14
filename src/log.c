/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:15:49 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 15:58:33 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/errprintf.h"

// printing on stderr because stdout could be redirected
int	log_msg(t_log_level level, char *msg, ...)
{
	va_list	args;

	if (level <= LOG_LEVEL)
	{
		if (PRINT_LOG_LEVEL)
		{	
			if (level == ERROR)
				errprintf("\033[41;37m ERORR \033[0m ");
			else if (level == WARNING)
				errprintf("\033[45;37m WARNING \033[0m ");
			else if (level == INFO)
				errprintf("\033[47;90m INFO \033[0m ");
			else if (level == DEBUG)
				errprintf("\033[103;90m DEBUG \033[0m ");
		}
		va_start(args, msg);
		verrprintf(msg, args);
		va_end(args);
		errprintf("\n");
	}
	return (SUCCESS);
}
