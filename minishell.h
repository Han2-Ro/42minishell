/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:13:22 by hrother           #+#    #+#             */
/*   Updated: 2024/04/17 19:05:02 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
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

// Global var for signals
extern int			g_sig;

typedef enum token_type
{
	NOTDEF,
	CMD,
	ARG,
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC,
	PIPE,
}					t_token_type;

typedef enum log_level
{
	ERROR,
	WARNING,
	INFO,
	DEBUG,
}					t_log_level;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_expand_info
{
	char			*str;
	unsigned int	i;
	unsigned int	var_idx;
	int				quote;
	t_list			*envp;
	int				status;
}					t_expand_info;

/**
 * @brief A command to be executed
 * @param bin the actual command.
 * @param args A list of strings.
 * @param in A list of input redirections
 * @param out A list of output redirections
 * @param pid The process id of the command
 */
typedef struct s_cmd
{
	char			*bin;
	char			**args;
	t_list			*redirects;
	int				fd_in;
	int				fd_out;
	int				pid;
	int				status;
}					t_cmd;

int					exec_cmd_list(t_list *cmd_list, t_list **envp, int *status);

// builtins
int					builtin_export(const t_cmd *cmd, t_list **envp);
int					builtin_unset(const t_cmd *cmd, t_list **envp);
int					builtin_env(const t_cmd *cmd, t_list **envp);
int					builtin_cd(const t_cmd *cmd, t_list **envp);
int					builtin_pwd(const t_cmd *cmd, t_list **envp);
int					builtin_exit(const t_cmd *cmd, t_list **envp);
int					builtin_echo(const t_cmd *cmd, t_list **envp);
int					is_builtin(const t_cmd *cmd);
int					exec_builtin(t_cmd *cmd, t_list **envp);

char				**get_paths(char **envp);
char				*path_to_bin(char *cmd, t_list *envp);

// redirects.c
int					redirs_to_fds(t_list *cmd_list);

int					here_doc(const char *delimiter, int *fd);

// lexer.c
t_list				*lexer(const char *line);
int					lex_split(t_list **token_lst);

// list_utils.c
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

// environment.c
void				free_env(void *content);
void				print_env(void *content);
char				*combine_key_value(char *key, char *value);
t_env				*new_env(char *key, char *value);
char				*ft_getenv(t_list *envlst, char *key);
/**
 * @brief Get the value from a string like "key=value"
 * @param arg The string to extract the value from
 * @return The value as a string, that must be freed or NULL on error
 */
char				*get_value(char *arg);
/**
 * @brief Get the key from a string like "key=value"
 * @param arg The string to extract the key from
 * @return The key as a string, that must be freed or NULL on error
 */
char				*get_key(char *arg);
t_list				*envp_to_list(char **envp);
char				**envlst_to_envp(t_list *envlst);

// expand.c
int					expand_tokens(t_list *token_lst, t_list *envp, int status);
char				*expand(char *string, t_list *envp, int status);

// print_structs.c
void				print_cmd(void *command);
void				print_token(void *token);
void				print_token_new(void *p_tkn);

// log.c
int					log_msg(t_log_level level, char *msg, ...);

// utils.c
t_cmd				*new_cmd(char *bin, char **args);
void				free_token(void *content);
void				free_cmd(void *content);
void				free_redir(void *content);
void				free_str_arr(char **strs, int size);
void				free_nullterm_str_arr(char **strs);
void				pass(void *content);

// loop.c
int					shell_loop(t_list *envp);

// signals.c
int					register_signals(void);

t_list				*parse(t_list *tokens);

#endif