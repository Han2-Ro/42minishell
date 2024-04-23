/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_funcheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:20:21 by hrother           #+#    #+#             */
/*   Updated: 2024/04/23 15:31:02 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*token_lst;
	t_list	*cmd_lst;
	char	*line;
	int		status;
	t_list	*env_list;

	(void)argc;
	(void)argv;
	status = 0;
	line = "echo \"$HOME\"|cat -e";
	env_list = envp_to_list(envp);
	if (!env_list)
		return (1);
	token_lst = lexer(line);
	expand_tokens_new(token_lst, env_list, status);
	if (token_lst)
	{
		cmd_lst = parse(token_lst);
		ft_lstiter(cmd_lst, print_cmd);
	}
	ft_lstclear(&env_list, free_env);
	ft_lstclear(&token_lst, free_token);
	ft_lstclear(&cmd_lst, free_cmd);
}
