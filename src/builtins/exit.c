/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:59:13 by hrother           #+#    #+#             */
/*   Updated: 2024/05/11 16:37:45 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_isspace(int c)
{
	if ((c == ' ') || (c == '\f') || (c == '\n')
		|| (c == '\r') || (c == '\t') || (c == '\v'))
		return (1);
	else
		return (0);
}

static int	ft_to_int(char *str)
{
	int				i;
	unsigned int	nbr;

	nbr = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr);
}

static int	get_exit_status(const char *nptr)
{
	char	*str;
	int		s;
	int		nbr;

	s = 1;
	str = (char *)nptr;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	nbr = ft_to_int(str);
	nbr *= s;
	while (ft_isdigit(*str))
		str++;
	while (ft_isspace(*str))
		str++;
	if (*str == '\0')
		return (nbr);
	log_msg(ERROR, "exit: numeric argument required");
	return (2);
}

// TODO: check if the argument is a 8-bit number
// TODO: free everthing before exit
int	builtin_exit(const t_cmd *cmd, int status)
{
	if (cmd->fd_in > 2 || cmd->fd_out > 2)
		return (0);
	printf("exit\n");
	log_msg(DEBUG, "executing builtin_exit");
	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		log_msg(ERROR, "exit: too many arguments");
		return (1);
	}
	if (cmd->args[1] != NULL)
	{
		status = get_exit_status(cmd->args[1]);
	}
	return (status | EXIT_MASK);
}
