/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:12:36 by hrother           #+#    #+#             */
/*   Updated: 2024/04/30 18:14:02 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	builtin_export(const t_cmd *cmd, t_list **envp);
int	builtin_unset(const t_cmd *cmd, t_list **envp);
int	builtin_env(const t_cmd *cmd, t_list **envp);
int	builtin_cd(const t_cmd *cmd, t_list **envp);
int	builtin_pwd(const t_cmd *cmd, t_list **envp);
int	builtin_exit(const t_cmd *cmd, int status);
int	builtin_echo(const t_cmd *cmd);

#endif
