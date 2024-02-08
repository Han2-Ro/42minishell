/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:26:15 by hrother           #+#    #+#             */
/*   Updated: 2024/02/08 16:23:40 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <string.h>

int	test_single_cmd(char *cmd, char **envp)
{
	t_cmd	exec;

	exec.bin = cmd;
	exec.args = malloc(sizeof(char *) * 2);
	exec.args[0] = cmd;
	exec.args[1] = NULL;
	exec.envp = envp;
	exec.fd_in = STDIN_FILENO;   // open("in", O_RDONLY);
	exec.fd_out = STDOUT_FILENO; // open("out", O_WRONLY);
	printf("in: %d, out: %d\n", exec.fd_in, exec.fd_out);
	return (exec_single_cmd(exec));
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	int res = test_single_cmd("/bin/ls", envp);
	printf("res: %d\n", res);
	if (res < 0)
	{
		printf("Error: %s\n", strerror(errno));
	}
	waitpid(res, NULL, 0);
}