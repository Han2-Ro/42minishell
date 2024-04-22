/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_new_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:19:38 by hrother           #+#    #+#             */
/*   Updated: 2024/04/21 11:19:56 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "utils/run_test.c"

int	compare_token_list(t_list *a, t_list *b)
{
	t_token	*token_a;
	t_token	*token_b;

	log_msg(INFO, "compare lists: %p, %p", a, b);
	while (a && b)
	{
		token_a = a->content;
		token_b = b->content;
		log_msg(INFO, "Comparing tokens:");
		print_token_new(token_a);
		print_token_new(token_b);
		if (token_a->type != token_b->type)
			return (FAILURE);
		if (token_a->value != token_b->value && ft_strncmp(token_a->value,
				token_b->value, ft_strlen(token_a->value) + 1))
			return (FAILURE);
		a = a->next;
		b = b->next;
		log_msg(INFO, "equal");
	}
	if (a || b)
		return (FAILURE);
	return (SUCCESS);
}

int	test_expander(char *line, t_list *expected, char **envp)
{
	t_list	*token_lst;
	t_list	*envp_lst;
	t_list	*new;
	int		status;
	int		result;

	log_msg(WARNING, "This test needs manual inspection of the output");
	status = 0;
	envp_lst = envp_to_list(envp);
	ft_lstadd_back(&envp_lst, ft_lstnew(new_env(ft_strdup("numbers"),
				ft_strdup("123456"))));
	ft_lstadd_back(&envp_lst, ft_lstnew(new_env(ft_strdup("empty"),
				ft_strdup(""))));
	ft_lstadd_back(&envp_lst, ft_lstnew(new_env(ft_strdup("double_quote"),
				ft_strdup("aaa\"bbb"))));
	ft_lstadd_back(&envp_lst, ft_lstnew(new_env(ft_strdup("single_quote"),
				ft_strdup("aaa\'bbb"))));
	new = ft_lstnew(new_env(ft_strdup("ll"), ft_strdup("ls -l -a")));
	ft_lstadd_back(&envp_lst, new);
	token_lst = lexer(line);
	result = expand_tokens_new(token_lst, envp_lst, status);
	ft_lstiter(token_lst, print_token_new);
	printf("Result: %i\n", result);
	result |= compare_token_list(token_lst, expected);
	ft_lstclear(&envp_lst, free_env);
	ft_lstclear(&token_lst, free_token);
	return (result);
}

int	test1(char **envp)
{
	t_list	*expected;
	t_token	token1;
	t_token	token2;
	int		result;

	token1.type = CMD;
	token1.value = "echo";
	token2.type = ARG;
	token2.value = "123456";
	expected = ft_lstnew(&token1);
	ft_lstadd_back(&expected, ft_lstnew(&token2));
	result = test_expander("echo $numbers", expected, envp);
	ft_lstclear(&expected, pass);
	return (result);
}

int	test2(char **envp)
{
	t_list	*expected;
	t_token	token1;
	t_token	token2;
	t_token	token3;
	t_token	token4;
	t_token	token5;
	int		result;

	token1.type = CMD;
	token1.value = "ls";
	token2.type = ARG;
	token2.value = "-l";
	token3.type = ARG;
	token3.value = "-a";
	token4.type = PIPE;
	token4.value = NULL;
	token5.type = CMD;
	token5.value = "cat";
	expected = ft_lstnew(&token1);
	ft_lstadd_back(&expected, ft_lstnew(&token2));
	ft_lstadd_back(&expected, ft_lstnew(&token3));
	ft_lstadd_back(&expected, ft_lstnew(&token4));
	ft_lstadd_back(&expected, ft_lstnew(&token5));
	result = test_expander("$ll|cat", expected, envp);
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	int result = SUCCESS;
	(void)argc;
	(void)argv;

	printf("\n-------- %s --------\n", argv[0]);
	result |= run_test("test1", test1, envp, true);
	result |= run_test("test2", test2, envp, true);
	printf("result: %d\n", result != SUCCESS);
	printf("------------ done ------------\n");
	return (result != SUCCESS);
}