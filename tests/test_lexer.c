/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:19:38 by hrother           #+#    #+#             */
/*   Updated: 2024/03/13 17:13:35 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils/run_test.c"

// int check(char *line, )

int	test_lexer(char **envp)
{
	t_list	*token_lst;
	char	*line;

	log_msg(WARNING, "This test needs manual inspection of the output");
	(void)envp;
	line = "echo";
	token_lst = lexer(line);
	ft_lstiter(token_lst, print_token_new);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int result = SUCCESS;
	(void)argc;
	(void)argv;

	printf("\n-------- %s --------\n", argv[0]);
	result |= run_test("test lexer", test_lexer, envp);
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}