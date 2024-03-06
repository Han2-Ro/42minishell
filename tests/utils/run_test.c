/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 14:49:40 by hannes            #+#    #+#             */
/*   Updated: 2024/03/06 19:57:54 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_test(char *name, int (*test)(char **), char **envp)
{
	int	result;
	int	pid;

	printf("\n------%s------\n", name);
	pid = fork();
	if (pid == 0)
	{
		result = test(envp);
		exit(result);
	}
	waitpid(pid, &result, 0);
	if (WIFEXITED(result) && WEXITSTATUS(result) == 0)
	{
		printf(GREEN "SUCCESS\n" RESET_COLOR);
		return (SUCCESS);
	}
	else
	{
		printf(RED "FAILURE\n" RESET_COLOR);
		return (FAILURE);
	}
}
