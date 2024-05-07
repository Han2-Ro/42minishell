#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// lexer_2.c
t_token	*lex_cmd(const char *line, unsigned int *i);
t_token	*lex_arg(const char *line, unsigned int *i);
t_token	*lex_redirect(const char *line, unsigned int *i);

#endif