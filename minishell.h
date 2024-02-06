/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:13:22 by hrother           #+#    #+#             */
/*   Updated: 2024/02/06 17:54:50 by hrother          ###   ########.fr       */
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

typedef enum e_node_type
{
	CMD,
	PIPE
}				t_node_type;

typedef struct s_node
{
	t_node_type	type;
	union
	{
		t_cmd	cmd;
		t_pipe	pipe;
	};
}				t_node;

typedef struct s_cmd
{
	char		*bin;
	char		**args;
	char		**envp;
}				t_cmd;

typedef struct s_pipe
{
	t_node		*child1;
	t_node		*child2;
}				t_pipe;

int				exec_cmd(const t_cmd exec, int fd_in, int fd_out);
int				exec_pipe(const t_pipe pipe, int fd_in, int fd_out);

#endif
