/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_cmd_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:29:23 by hrother           #+#    #+#             */
/*   Updated: 2024/03/03 19:21:26 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils/run_test.c"

int	test_file_file(char **envp)
{
	t_list	*cmd_list;
	int		return_value;

	cmd_list = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/grep", (char *[]){"/bin/grep",
				"test", NULL}, envp));
	print_list(cmd_list);
	return_value = exec_cmd_line(cmd_list, "tests/files/in",
			"tests/files/out_01");
	destroy_list(cmd_list);
	return (return_value != SUCCESS);
}

int	test_std_std(char **envp)
{
	t_list	*cmd_list;
	int		return_value;

	cmd_list = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/usr/sbin/ifconfig",
				(char *[]){"/usr/sbin/ifconfig", NULL}, envp));
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/grep", (char *[]){"/bin/grep",
				"inet", NULL}, envp));
	print_list(cmd_list);
	return_value = exec_cmd_line(cmd_list, NULL, NULL);
	destroy_list(cmd_list);
	return (return_value != SUCCESS);
}

int	test_file_std(char **envp)
{
	t_list	*cmd_list;
	int		return_value;

	cmd_list = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/cat", (char *[]){"/bin/cat",
				"tests/files/in", NULL}, envp));
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/grep", (char *[]){"/bin/grep",
				"test", NULL}, envp));
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/wc", (char *[]){"/bin/wc",
				"-l", NULL}, envp));
	print_list(cmd_list);
	return_value = exec_cmd_line(cmd_list, "tests/files/in", NULL);
	destroy_list(cmd_list);
	return (return_value != SUCCESS);
}

int	test_std_file(char **envp)
{
	t_list	*cmd_list;
	int		return_value;

	cmd_list = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/ls", (char *[]){"/bin/ls",
				"-l", NULL}, envp));
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/grep", (char *[]){"/bin/grep",
				"d", NULL}, envp));
	print_list(cmd_list);
	return_value = exec_cmd_line(cmd_list, NULL, "tests/files/out_02");
	destroy_list(cmd_list);
	return (return_value != SUCCESS);
}

int	test_unexisting_infile(char **envp)
{
	t_list	*cmd_list;
	int		return_value;

	cmd_list = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/cat", (char *[]){"/bin/cat",
				"-e", NULL}, envp));
	print_list(cmd_list);
	return_value = exec_cmd_line(cmd_list, "tests/files/nofile",
			"tests/files/out_03");
	destroy_list(cmd_list);
	return (return_value == SUCCESS);
}

int	test_no_perm_outfile(char **envp)
{
	t_list	*cmd_list;
	int		return_value;

	cmd_list = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/cat", (char *[]){"/bin/cat",
				"-e", NULL}, envp));
	print_list(cmd_list);
	return_value = exec_cmd_line(cmd_list, "tests/files/in",
			"tests/files/no_perm");
	destroy_list(cmd_list);
	return (return_value == SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int result = SUCCESS;
	(void)argc;
	(void)argv;

	printf("\n-------- %s --------\n", argv[0]);
	result |= run_test("test file in, file out", test_file_file, envp);
	result |= run_test("test std in, std out", test_std_std, envp);
	result |= run_test("test file in, std out", test_file_std, envp);
	result |= run_test("test std in, file out", test_std_file, envp);
	result |= run_test("test unexisting infile", test_unexisting_infile, envp);
	result |= run_test("test no perm outfile", test_no_perm_outfile, envp);
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}