/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errprintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:26:07 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 15:01:03 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRPRINTF_H
# define ERRPRINTF_H

# define ERR_SYNTAX_AT_C "syntax error near unexpected token `%s'"

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		errprintf(const char *str, ...);
int     verrprintf(const char *str, va_list args);

int		errprint_c(char c);
int		errprint_s(char *s);
int		errprint_i(int n);
size_t	ft_strlen(const char *str);

#endif
