/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:15:49 by hrother           #+#    #+#             */
/*   Updated: 2024/02/28 19:21:35 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	log_msg(t_log_level level, char *msg, ...)
{
	va_list	args;

	// TODO: dont use forbidden funtion fprintf
	// printing on stderr because stdout could be redirected
	if (level <= LOG_LEVEL)
	{
		if (level == ERROR)
			fprintf(stderr, "ERROR: ");
		else if (level == WARNING)
			fprintf(stderr, "WARNING: ");
		else if (level == INFO)
			fprintf(stderr, "INFO: ");
		else if (level == DEBUG)
			fprintf(stderr, "DEBUG: ");
		va_start(args, msg);
		vfprintf(stderr, msg, args);
		va_end(args);
		fprintf(stderr, "\n");
	}
	return (SUCCESS);
}
