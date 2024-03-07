/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:33:22 by hrother           #+#    #+#             */
/*   Updated: 2024/03/07 16:46:29 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils/run_test.c"

int	test_null(char **envp)
{
	t_list	*tokens;
	t_list	*cmds;

	tokens = NULL;
	cmds = parse(tokens, envp);
	ft_lstiter(cmds, print_cmd);
	if (cmds == NULL)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int	result;

	result = SUCCESS;
	(void)argc;
	(void)argv;
	printf("\n-------- %s --------\n", argv[0]);
	result |= run_test("test_null", test_null, envp);
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}
