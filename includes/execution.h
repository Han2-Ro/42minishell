/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:05:16 by hrother           #+#    #+#             */
/*   Updated: 2024/04/30 18:11:22 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

int		exec_cmd(t_cmd *cmd, t_list *cmd_list, t_list **envlst, int status);
void	close_fds(void *content);
char	*path_to_bin(char *cmd, t_list *envp);

#endif
