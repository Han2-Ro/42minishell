/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:46 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/25 10:45:49 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_prompt(t_evars *evars, char *buf, size_t len)
{
	char	*temp;
	char	*pwd;
	char	*home;
	char	*end;

	end = "\033[32m > \033[0m";
	if (evars->status != 0)
		end = "\033[31m > \033[0m";
	ft_bzero(buf, len);
	pwd = get_envvalue(evars->envl, "PWD");
	home = get_envvalue(evars->envl, "HOME");
	temp = pwd;
	ft_strlcat(buf, "\033[36m~", len);
	if (home && pwd && !ft_strncmp(home, pwd, ft_strlen(home)))
	{
		temp += ft_strlen(home);
		ft_strlcat(buf, temp, len);
	}
	else if (pwd)
		ft_strlcat(buf, pwd, len);
	else
		ft_strlcat(buf, "爪丨几丨丂卄乇ㄥㄥ\33[22m", len);
	ft_strlcat(buf, end, len);
	return (SUCCESS);
}
