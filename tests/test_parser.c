/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:33:22 by hrother           #+#    #+#             */
/*   Updated: 2024/03/07 17:05:44 by hrother          ###   ########.fr       */
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

int	test_1cmd(char **envp)
{
	t_list	*tokens;
	t_list	*cmds;
	t_cmd	*cmd;
	t_token	token;

	tokens = NULL;
	token = (t_token){.type = CMD, .value = "echo"};
	ft_lstadd_back(&tokens, ft_lstnew(&token));
	token = (t_token){.type = ARG, .value = "Hello"};
	ft_lstadd_back(&tokens, ft_lstnew(&token));
	token = (t_token){.type = R_OUT, .value = "out.txt"};
	ft_lstadd_back(&tokens, ft_lstnew(&token));
	cmds = parse(tokens, envp);
	ft_lstiter(cmds, print_cmd);
	if (cmds == NULL)
		return (FAILURE);
	if (ft_lstsize(cmds) != 1)
		return (FAILURE);
	cmd = (t_cmd *)cmds->content;
	if (ft_strncmp(cmd->bin, "echo", 10) != 0)
		return (FAILURE);
	if (ft_strncmp(cmd->args[0], "Hello", 10) != 0)
		return (FAILURE);
	if (cmd->args[1] != NULL)
		return (FAILURE);
	if (ft_lstsize(cmd->in) != 0)
		return (FAILURE);
	if (ft_lstsize(cmd->out) != 1)
		return (FAILURE);
	if (ft_strncmp(((t_redirect *)cmd->out->content)->filename, "out.txt",
			10) != 0)
		return (FAILURE);
	// TODO: cmd->envp and cmd->pid is not checked
	// TODO: free everything
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int	result;

	result = SUCCESS;
	(void)argc;
	(void)argv;
	printf("\n-------- %s --------\n", argv[0]);
	result |= run_test("test_null", test_null, envp);
	result |= run_test("test_1cmd", test_1cmd, envp);
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}
