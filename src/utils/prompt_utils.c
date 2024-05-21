/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/22 01:11:27 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_prompt(t_evars *evars)
{
	char	*prompt;
	char	*temp;
	char	*pwd;
	char	*home;
	char	*end;

	end = "\033[32m > \033[0m";
	if (evars->status != 0)
		end = "\033[31m > \033[0m";
	prompt = NULL;
	pwd = get_envvalue(evars->envl, "PWD");
	home = get_envvalue(evars->envl, "HOME");
	temp = pwd;
	if (home && pwd && !ft_strncmp(home, pwd, ft_strlen(home)))
	{
		temp += ft_strlen(home);
		prompt = vstrjoin(3, "\033[36m~", temp, end);
	}
	else if (pwd)
		prompt = vstrjoin(3, "\033[36m", pwd, end);
	else
		prompt = vstrjoin(3, "\033[1;36m", "爪丨几丨丂卄乇ㄥㄥ\33[22m", end);
	return (prompt);
}
