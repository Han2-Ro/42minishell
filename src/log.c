/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:15:49 by hrother           #+#    #+#             */
/*   Updated: 2024/05/07 12:40:36 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: dont use forbidden funtions fprintf and vfprintf
// TODO: add __FILE__, __LINE__ option
// printing on stderr because stdout could be redirected
int	log_msg(t_log_level level, char *msg, ...)
{
	va_list	args;

	if (level <= LOG_LEVEL)
	{
		if (level == ERROR)
			fprintf(stderr, "\033[41;37m ERORR \033[0m ");
		else if (level == WARNING)
			fprintf(stderr, "\033[45;37m WARNING \033[0m ");
		else if (level == INFO)
			fprintf(stderr, "\033[47;90m INFO \033[0m ");
		else if (level == DEBUG)
			fprintf(stderr, "\033[103;90m DEBUG \033[0m ");
		va_start(args, msg);
		vfprintf(stderr, msg, args);
		va_end(args);
		fprintf(stderr, "\n");
	}
	return (SUCCESS);
}
