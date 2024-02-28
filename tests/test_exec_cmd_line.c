/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_cmd_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:46:55 by hrother           #+#    #+#             */
/*   Updated: 2024/02/28 16:09:49 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils/run_test.c"

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
	// destroy_list(cmd_list);
	return (result);
}

int	test_rw_file(char **envp)
{
	t_list	*cmd_list;
	int		result;
	int		in;
	int		out;

	cmd_list = NULL;
	t_cmd cmd1 = {
		.bin = "/bin/grep",
		.args = (char *[]){"grep", "test", NULL},
		.envp = envp,
	};
	cmd_list = ft_lstadd(&cmd_list, &cmd1);
	print_list(cmd_list);
	in = open("in", O_RDONLY);
	out = open("out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	result = exec_cmd_line(cmd_list, in, out);
	close(in);
	close(out);
	// destroy_list(cmd_list);
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	int result = SUCCESS;
	(void)argc;
	(void)argv;

	printf("\n-------- %s --------\n", argv[0]);
	result |= run_test("test_1cmd", test_1cmd, envp);
	result |= run_test("test_2cmds", test_2cmds, envp);
	result |= run_test("test_3cmds", test_3cmds, envp);
	result |= run_test("test_rw_file", test_rw_file, envp);
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}