/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_cmd_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:46:55 by hrother           #+#    #+#             */
/*   Updated: 2024/02/11 16:09:23 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	test_2cmds(char **envp)
{
	t_list	*cmd_list;

	cmd_list = NULL;
	t_cmd cmd1 = {
		.bin = "/bin/ls",
		.args = (char *[]){"ls", "-l", NULL},
		.envp = envp,
	};
	t_cmd cmd2 = {
		.bin = "/bin/grep",
		.args = (char *[]){"grep", "d", NULL},
		.envp = envp,
	};
	cmd_list = ft_lstadd(&cmd_list, &cmd1);
	cmd_list = ft_lstadd(&cmd_list, &cmd2);
	print_list(cmd_list);
	exec_cmd_line(cmd_list, STDIN_FILENO, STDOUT_FILENO);
	// destroy_list(cmd_list);
	return (SUCCESS);
}

int	test_3cmds(char **envp)
{
	t_list	*cmd_list;

	cmd_list = NULL;
	t_cmd cmd1 = {
		.bin = "/bin/ls",
		.args = (char *[]){"ls", "-l", NULL},
		.envp = envp,
	};
	t_cmd cmd2 = {
		.bin = "/bin/grep",
		.args = (char *[]){"grep", "d", NULL},
		.envp = envp,
	};
	t_cmd cmd3 = {
		.bin = "/bin/wc",
		.args = (char *[]){"wc", "-l", NULL},
		.envp = envp,
	};
	cmd_list = ft_lstadd(&cmd_list, &cmd1);
	cmd_list = ft_lstadd(&cmd_list, &cmd2);
	cmd_list = ft_lstadd(&cmd_list, &cmd3);
	print_list(cmd_list);
	exec_cmd_line(cmd_list, STDIN_FILENO, STDOUT_FILENO);
	// destroy_list(cmd_list);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	printf("\n-------- %s --------\n", argv[0]);
	printf("\ntest_2cmd\n");
	test_2cmds(envp);
	printf("\ntest_3cmd\n");
	test_3cmds(envp);
	printf("------------ done ------------\n");
}