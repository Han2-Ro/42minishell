/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:13:22 by hrother           #+#    #+#             */
/*   Updated: 2024/03/06 17:08:20 by hrother          ###   ########.fr       */
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
#  define LOG_LEVEL DEBUG
# endif

typedef enum log_level
{
	ERROR,
	WARNING,
	INFO,
	DEBUG,
}					t_log_level;

typedef struct s_env
{
	char			*value;
}					t_env;

typedef struct s_redirects
{
	char			*filename;
}					t_redirects;

typedef struct s_cmd
{
	char			*bin;
	char			**args;
	char			**envp;
	t_redirects		*in;
	t_redirects		*out;
	int				pid;
}					t_cmd;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					exec_single_cmd(const t_cmd exec, int fd_in, int fd_out,
						int to_close);
int					exec_cmd_list(t_list *cmd_list, int fd_in, int fd_out);
int					exec_cmd_line(t_list *cmd_list, const char *in_file,
						const char *out_file);

int					run_cmd(const char *cmd, char *envp[]);

char				**get_paths(char **envp);
char				*path_to_bin(char *cmd);

t_list				*ft_lstnew_old(t_cmd *cmd);
t_list				*ft_lstadd(t_list **lst, t_cmd *cmd);
void				destroy_list(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);

// print_structs.c
void				print_cmd(t_cmd *cmd);
void				print_list(t_list *lst);

// log.c
int					log_msg(t_log_level level, char *msg, ...);
t_cmd				*new_cmd(char *bin, char **args, char **envp);

// loop.c
int					shell_loop(char *envp[]);

#endif
