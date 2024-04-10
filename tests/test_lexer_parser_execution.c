/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_parser_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:39:38 by hrother           #+#    #+#             */
/*   Updated: 2024/04/10 19:51:59 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils/run_test.c"

int	test_general(char *line, int token_count, int cmd_count, char **envp)
{
	t_list	*token_lst;
	t_list	*cmd_lst;
	t_list	*envp_list;

	envp_list = envp_to_list(envp);
	log_msg(WARNING, "This tests has some automatic checks,");
	log_msg(WARNING, "but still needs manual inspection of the output.");
	log_msg(INFO, "Input line: %s", line);
	token_lst = lexer(line);
	ft_lstiter(token_lst, print_token_new);
	if (ft_lstsize(token_lst) != token_count)
		return (log_msg(ERROR, "Token list has wrong size."), FAILURE);
	cmd_lst = parse(token_lst);
	if (ft_lstsize(cmd_lst) != cmd_count)
		return (log_msg(ERROR, "Command list has wrong size."), FAILURE);
	ft_lstiter(cmd_lst, print_cmd);
	exec_cmd_list(cmd_lst, &envp_list, 0);
	return (SUCCESS);
}

int	test1(char **envp)
{
	printf("test1\n");
	return (test_general("ls -l|grep d > tests/files/out_01|wc -l", 9, 3,
			envp));
}

int	test2(char **envp)
{
	return (test_general("<tests/files/in_01 cat < tests/files/in_02 -e", 4, 1,
			envp));
}

int	main(int argc, char **argv, char **envp)
{
	int result = SUCCESS;
	(void)argc;
	(void)argv;

	printf("\n-------- %s --------\n", argv[0]);
#ifndef GITHUB_ACTIONS
	result |= run_test("test1", test1, envp, true);
#endif

	result |= run_test("test2", test2, envp, true);
	// TODO: Add more tests
	// TODO: Test error cases
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}