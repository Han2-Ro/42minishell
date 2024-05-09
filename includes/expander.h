/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:04:57 by hrother           #+#    #+#             */
/*   Updated: 2024/05/08 13:10:18 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

int					get_quote(int quote, const char c);
int					handle_quote(unsigned int i, char **str, int *quote);
char				*str_insert(char const *i_str, char *o_str,
						unsigned int from, unsigned int to);
int					expand_tokens(t_list *token_lst, t_list *envp, int status);
char				*expand(char *string, t_list *envp, int status);
t_list				*split_token(char *str, int *i, int to);
int					replace_dollar(char **str, int i, const t_evars evars);
void				handle_dollar(t_list ***list, int *i, const t_evars evars,
						const int quote);

#endif