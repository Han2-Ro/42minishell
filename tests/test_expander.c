/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:19:38 by hrother           #+#    #+#             */
/*   Updated: 2024/04/16 19:23:34 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils/run_test.c"

// int check(char *line, )
//void	expand(t_token *token, t_list *envp, int status);

int	test_expander(char **envp)
{
	t_list	*envp_lst;
	int		status;
	char	*expanded_str;

	status = 0;
	envp_lst = envp_to_list(envp);
	
	expanded_str = expand("$ end", envp_lst, status);
	printf("%s\n", expanded_str);
	ft_lstclear(&envp_lst, free_env);
	return (SUCCESS);

	/*
	//t_list	*token_lst;
	// char	*line;
	t_list	*token_lst;
	t_list	*envp_lst;
	int		status;
	int		result;
	log_msg(WARNING, "This test needs manual inspection of the output");

	status = 0;
	envp_lst = envp_to_list(envp);
	token_lst = lexer("echo $USER");
	
	result = expand_tokens(token_lst, envp_lst, status);
	if (result)
	{
		ft_lstclear(&envp_lst, free_env);
		ft_lstclear(&token_lst, free_token);
		return (FAILURE);
	}
	ft_lstiter(token_lst, print_token_new);
	// line = "echo www|cat>out>>END";
	// token_lst = lexer(line);

	ft_lstclear(&envp_lst, free_env);
	ft_lstclear(&token_lst, free_token);
	printf("Result: %i\n", result);
	// ft_lstclear(&token_lst, free_token);
	return (SUCCESS);*/
}

int	main(int argc, char **argv, char **envp)
{
	int result = SUCCESS;
	(void)argc;
	(void)argv;

	printf("\n-------- %s --------\n", argv[0]);
	result |= run_test("test expander", test_expander, envp , true);
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}