/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_cmd_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:46:55 by hrother           #+#    #+#             */
/*   Updated: 2024/03/25 15:56:47 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils/run_test.c"

int	test_1cmd(char **envp)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	t_list	*envp_list;
	t_token	redirect;
	char	**args;

	envp_list = envp_to_list(envp);
	log_msg(WARNING, "This test needs manual inspection of the output");
	cmd_list = NULL;
	args = malloc(sizeof(char *) * 3);
	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	cmd = new_cmd("/bin/ls", args);
	redirect.type = R_OUT;
	redirect.value = "tests/files/out_02";
	ft_lstadd_back(&cmd->redirects, ft_lstnew(&redirect));
	cmd_list = ft_lstadd(&cmd_list, cmd);
	ft_lstiter(cmd_list, print_cmd);
	exec_cmd_list(cmd_list, &envp_list);
	ft_lstclear(&envp_list, free_env);
	return (SUCCESS);
}

int	test_2cmds(char **envp)
{
	t_list	*cmd_list;
	t_list	*envp_list;
	char	**args1;
	char	**args2;

	envp_list = envp_to_list(envp);
	log_msg(WARNING, "This test needs manual inspection of the output");
	cmd_list = NULL;
	args1 = malloc(sizeof(char *) * 3);
	args1[0] = "ls";
	args1[1] = "-l";
	args1[2] = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/ls", args1));
	args2 = malloc(sizeof(char *) * 3);
	args2[0] = "grep";
	args2[1] = "d";
	args2[2] = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/grep", args2));
	ft_lstiter(cmd_list, print_cmd);
	exec_cmd_list(cmd_list, &envp_list);
	ft_lstclear(&envp_list, free_env);
	return (SUCCESS);
}

int	test_3cmds(char **envp)
{
	t_list	*cmd_list;
	int		result;
	t_list	*envp_list;
	char	**args1;
	char	**args2;
	char	**args3;

	envp_list = envp_to_list(envp);
	log_msg(WARNING, "This test needs manual inspection of the output");
	cmd_list = NULL;
	args1 = malloc(sizeof(char *) * 3);
	args1[0] = "ls";
	args1[1] = "-l";
	args1[2] = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/ls", args1));
	args2 = malloc(sizeof(char *) * 3);
	args2[0] = "grep";
	args2[1] = "d";
	args2[2] = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/grep", args2));
	args3 = malloc(sizeof(char *) * 3);
	args3[0] = "wc";
	args3[1] = "-l";
	args3[2] = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/wc", args3));
	ft_lstiter(cmd_list, print_cmd);
	result = exec_cmd_list(cmd_list, &envp_list);
	ft_lstclear(&envp_list, free_env);
	return (result);
}

/*
int	test_rw_file(char **envp)
{
	t_list	*cmd_list;
	int		result;
	int		in;
	int		out;

	log_msg(WARNING, "This test needs manual inspection of the output");
	cmd_list = NULL;
	cmd_list = ft_lstadd(&cmd_list, new_cmd("/bin/grep", (char *[]){"grep",
				"test", NULL}, envp));
	ft_lstiter(cmd_list, print_cmd);
	in = open("tests/files/in", O_RDONLY);
	out = open("tests/files/out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	result = exec_cmd_list(cmd_list, in, out);
	close(in);
	close(out);
	destroy_list(cmd_list);
	return (result);
}
*/

int	main(int argc, char **argv, char **envp)
{
	int result = SUCCESS;
	(void)argc;
	(void)argv;

	printf("\n-------- %s --------\n", argv[0]);
	result |= run_test("test_1cmd", test_1cmd, envp, true);
	result |= run_test("test_2cmds", test_2cmds, envp, true);
	result |= run_test("test_3cmds", test_3cmds, envp, true);
	// result |= run_test("test_rw_file", test_rw_file, envp , true);
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}