/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:13:22 by hrother           #+#    #+#             */
/*   Updated: 2024/02/08 15:32:07 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE -1

typedef struct s_list
{
	t_cmd			*cmd;
	struct s_list	*next;
}					t_list;

typedef struct s_cmd
{
	char			*bin;
	char			**args;
	char			**envp;
}					t_cmd;

int					exec_single_cmd(const t_cmd exec, int fd_in, int fd_out);
int					exec_cmd_line(const t_list *cmd_list, int fd_in,
						int fd_out);

#endif
