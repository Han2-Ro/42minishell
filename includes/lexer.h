/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:33:22 by hrother           #+#    #+#             */
/*   Updated: 2024/06/09 11:23:41 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// lexer_2.c
t_token	*lex_arg(const char *line, unsigned int *i);
t_token	*lex_redirect(const char *line, unsigned int *i);

#endif