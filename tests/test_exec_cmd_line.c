/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_cmd_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:46:55 by hrother           #+#    #+#             */
/*   Updated: 2024/02/25 14:30:12 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	test_1cmd(char **envp)
{
	t_list	*cmd_list;

	cmd_list = NULL;
	t_cmd cmd = {
		.bin = "/bin/ls",
		.args = (char *[]){"ls", "-l", NULL},
		.envp = envp,
	};
	cmd_list = ft_lstadd(&cmd_list, &cmd);
	print_list(cmd_list);
	exec_cmd_line(cmd_list, STDIN_FILENO, STDOUT_FILENO);
	// destroy_list(cmd_list);
	return (SUCCESS);
}

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
	int		result;

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
	result = exec_cmd_line(cmd_list, STDIN_FILENO, STDOUT_FILENO);
	destroy_list(cmd_list);
	return (result);
}

int	run_test(char *name, int (*test)(char **), char **envp)
{
	int	result;

	printf("\n%s\n", name);
	result = test(envp);
	if (result == SUCCESS)
		printf(GREEN "SUCCESS\n" RESET_COLOR);
	else
		printf(RED "FAILURE\n" RESET_COLOR);
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	printf("\n-------- %s --------\n", argv[0]);
	run_test("test_1cmd", test_1cmd, envp);
	run_test("test_2cmds", test_2cmds, envp);
	run_test("test_3cmds", test_3cmds, envp);
	printf("------------ done ------------\n");
}