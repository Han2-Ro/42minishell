/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:40:49 by hrother           #+#    #+#             */
/*   Updated: 2024/03/06 19:50:43 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils/run_test.c"

int	test_pwd(char **envp)
{
	t_cmd	cmd;

	log_msg(WARNING, "This test needs manual inspection of the output");
	cmd.bin = "pwd";
	cmd.args = (char *[]){"pwd", NULL};
	cmd.envp = envp;
	exec_builtin(cmd);
	return (FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int result = SUCCESS;
	(void)argc;
	(void)argv;

	printf("\n-------- %s --------\n", argv[0]);
	result |= run_test("test_pwd", test_pwd, envp);
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}