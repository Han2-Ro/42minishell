/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_funcheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:20:21 by hrother           #+#    #+#             */
/*   Updated: 2024/05/07 17:07:04 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*token_lst;
	t_list	*cmd_lst;
	char	*line;
	t_evars	evars;

	cmd_lst = NULL;
	(void)argc;
	(void)argv;
	evars.status = 0;
	line = "echo $var";
	evars.envp = envp_to_list(envp);
	ft_lstadd_back(&evars.envp, ft_lstnew(new_env(ft_strdup("var"), ft_strdup("aa $? bb"))));
	if (!evars.envp)
		return (1);
	token_lst = lexer(line);
	expand_token_list(&token_lst, evars);
	ft_lstiter(token_lst, print_token);
	if (token_lst)
	{
		cmd_lst = parse(token_lst);
		ft_lstiter(cmd_lst, print_cmd);
	}
	ft_lstclear(&evars.envp, free_env);
	ft_lstclear(&token_lst, free_token);
	ft_lstclear(&cmd_lst, free_cmd);
}
