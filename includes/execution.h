/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:05:16 by hrother           #+#    #+#             */
/*   Updated: 2024/05/12 16:06:57 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

int     exec_cmd(t_cmd *cmd, t_list *cmd_list, t_evars *evars);
void	close_fds(void *content);
char	*path_to_bin(char *cmd, t_list *envp);

// redirects
int		redirs_to_fds(t_list *cmd_list, t_evars *evars);
int		here_doc(const t_token *token, int *fd, t_evars *evars);

// builtins
int		is_builtin(const t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_list **envp, int status);

#endif
