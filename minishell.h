/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:13:22 by hrother           #+#    #+#             */
/*   Updated: 2024/03/03 17:25:07 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define RED "\x1b[31m"
# define YELLOW "\x1b[33m"
# define GREEN "\x1b[32m"
# define RESET_COLOR "\x1b[0m"

# define SUCCESS 0
# define FAILURE -1

# ifndef LOG_LEVEL
#  define LOG_LEVEL WARNING
# endif

typedef enum log_level
{
	ERROR,
	WARNING,
	INFO,
	DEBUG,
}					t_log_level;

typedef struct s_cmd
{
	char			*bin;
	char			**args;
	char			**envp;
	int				pid;
}					t_cmd;

typedef struct s_list
{
	t_cmd *cmd; // consider not using a pointer, so we don't have to malloc
	struct s_list	*next;
}					t_list;

int					exec_single_cmd(const t_cmd exec, int fd_in, int fd_out,
						int to_close);
int					exec_cmd_list(t_list *cmd_list, int fd_in, int fd_out);
int					exec_cmd_line(t_list *cmd_list, const char *in_file,
						const char *out_file);

int					run_cmd(const char *cmd, char *envp[]);

char				**get_paths(char **envp);
char				*path_to_bin(char **folders, char *cmd);

t_list				*ft_lstnew(t_cmd *cmd);
t_list				*ft_lstadd(t_list **lst, t_cmd *cmd);
void				destroy_list(t_list *lst);

// print_structs.c
void				print_cmd(t_cmd *cmd);
void				print_list(t_list *lst);

// log.c
int					log_msg(t_log_level level, char *msg, ...);
t_cmd				*new_cmd(char *bin, char **args, char **envp);

// loop.c
int					shell_loop(char *envp[]);

#endif
