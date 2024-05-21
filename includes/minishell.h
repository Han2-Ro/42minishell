/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:10:11 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/22 00:48:55 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

# define WHITESPACE " \t\n\r\v\f"
# define SPECIAL_CHARS "$<>|\'\""

# define PROMPT "ms> "

# define STATUS_MASK 0x000000ff
# define EXIT_MASK 0x00000100

# define MSG_WRONG_ARGC "wrong number of arguments"
# define MSG_SYNTAX_ERR_NEAR "syntax error near unexpected token `%c'"

# ifndef PRINT_LOG_LEVEL
#  define PRINT_LOG_LEVEL false
# endif

# ifndef LOG_LEVEL
#  define LOG_LEVEL INFO
# endif

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
	R_QUOTEDOC
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

typedef struct s_evars
{
	t_list			*envl;
	int				status;
	int				tty;
}					t_evars;

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
	int				is_pipeline;
	int				status;
}					t_cmd;

int					exec_cmd_list(t_list *cmd_list, t_evars *evars);

// lexer.c
t_list				*lexer(const char *line, int *status);

// list_utils.c
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
void				ft_lstinsert(t_list *insert_after, t_list *list);
void				ft_lstrmvone(t_list **head, t_list *node,
						void (*del)(void *));

// environment.c
void				free_env(void *content);
void				print_env(void *content);
char				*combine_key_value(char *key, char *value);
t_env				*new_env(char *key, char *value);
const t_list		*find_env(const t_list *list, const char *key);
char				*get_envvalue(const t_list *envlst, const char *key);
/**
	* @brief Get the value from a string like "key=value"
	* @param arg The string to extract the value from
	* @return The value as a string,
		that must be freed or NULL on error
	*/
char				*get_value(const char *arg);
/**
	* @brief Get the key from a string like "key=value"
	* @param arg The string to extract the key from
	* @return The key as a string,
		that must be freed or NULL on error
	*/
char				*get_key(const char *arg);
t_list				*envp_to_list(char **envp);
char				**envlst_to_envp(t_list *envlst);

// expander.c
int					expand_heredoc(char **str, const t_evars evars);
int					expand_token_list(t_list **token_lst, const t_evars evars);

// print_structs.c
void				print_cmd(void *command);
void				print_token(void *token);
void				print_token_new(void *p_tkn);

// log.c
int					log_msg(t_log_level level, char *msg, ...);

// utils.c
bool				fd_is_pipe(int fd);
t_cmd				*new_cmd(char *bin, char **args);
void				free_token(void *content);
void				free_cmd(void *content);
void				free_redir(void *content);
void				free_str_arr(char **strs, int size);
void				free_nullterm_str_arr(char **strs);
int					is_space(char c);
void				pass(void *content);
int					is_space(char c);
int					ft_strcmp(const char *s1, const char *s2);
void				skip_until(const char *str, unsigned int *i,
						const char *charset, bool val);
t_token				*new_token(t_token_type type, char *value);
char				*read_next_line(int fd);
char				*vstrjoin(int nbr_of_strs, ...);
void				set_is_pipeline(t_list *cmds);
bool				dont_run(const t_cmd *cmd);

char				*get_prompt(t_evars *evars);

// loop.c
char				*ft_readline(char *prompt, int tty);
int					shell_loop(t_list *envp, int tty);

// signals.c
int					idle_signals(void);
int					active_signals(void);

int					export_env_var(t_list **envp, char *key, char *value);

t_list				*parse(t_list *tokens);

#endif