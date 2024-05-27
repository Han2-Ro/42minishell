/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/27 17:05:33 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(t_evars *evars)
{
	char	*prompt;
	char	*temp;
	char	*pwd;
	char	*home;
	char	*end;

	end = "\001\033[32m\002 > \001\033[0m\002";
	if (evars->status != 0)
		end = "\001\033[31m\002 > \001\033[0m\002";
	prompt = NULL;
	pwd = get_envvalue(evars->envl, "PWD");
	home = get_envvalue(evars->envl, "HOME");
	temp = pwd;
	if (home && pwd && !ft_strncmp(home, pwd, ft_strlen(home)))
	{
		temp += ft_strlen(home);
		prompt = vstrjoin(3, "\001\033[36m\002~", temp, end);
	}
	else if (pwd)
		prompt = vstrjoin(3, "\001\033[36m\002", pwd, end);
	else
		prompt = vstrjoin(3, "\001\033[1;36m\002", "爪丨几丨丂卄乇ㄥㄥ\001\33[22m\002",
				end);
	return (prompt);
}
