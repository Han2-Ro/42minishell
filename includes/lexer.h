/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:33:22 by hrother           #+#    #+#             */
/*   Updated: 2024/05/09 13:33:23 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// lexer_2.c
t_token	*lex_cmd(const char *line, unsigned int *i);
t_token	*lex_arg(const char *line, unsigned int *i);
t_token	*lex_redirect(const char *line, unsigned int *i);

#endif