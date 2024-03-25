/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:59:50 by aprevrha          #+#    #+#             */
/*   Updated: 2024/03/25 15:23:47 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/ioctl.h>

int	g_sig = 0;

void	signal_handler(int signum)
{
	g_sig = signum;
	log_msg(INFO, "Signal: %i", signum);
	if (signum == SIGINT)
	{
		
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_redisplay();
	}
		
}


int	register_signals(void)
{
	struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
		log_msg(ERROR, "failed to register signal SIGINT");
        return (1);
    }
	if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("sigaction");
		log_msg(ERROR, "failed to register signal SIGINT");
        return (1);
    }
	return (0);
}
