/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_parser_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:39:38 by hrother           #+#    #+#             */
/*   Updated: 2024/03/13 16:19:29 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils/run_test.c"

int	test_general(char *line, int token_count, int cmd_count, char **envp)
{
	t_list	*token_lst;
	t_list	*cmd_lst;

	log_msg(WARNING, "This tests has some automatic checks,");
	log_msg(WARNING, "but still needs manual inspection of the output.");
	log_msg(INFO, "Input line: %s", line);
	token_lst = lexer(line);
	if (ft_lstsize(token_lst) != token_count)
		return (log_msg(ERROR, "Token list has wrong size."), FAILURE);
	cmd_lst = parse(token_lst, envp);
	if (ft_lstsize(cmd_lst) != cmd_count)
		return (log_msg(ERROR, "Command list has wrong size."), FAILURE);
	redirs_to_fds(cmd_lst);
	exec_cmd_list(cmd_lst);
	return (SUCCESS);
}

int	test1(char **envp)
{
	return (test_general("ls -l|grep d > tests/files/out_01|wc -l", 9, 3,
			envp));
}

int	test2(char **envp)
{
	return (test_general("<tests/files/in_01 cat< tests/files/in_02 -e", 4, 1,
			envp));
}

int	main(int argc, char **argv, char **envp)
{
	int result = SUCCESS;
	(void)argc;
	(void)argv;

	printf("\n-------- %s --------\n", argv[0]);
	result |= run_test("test1", test1, envp);
	result |= run_test("test2", test2, envp);
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}