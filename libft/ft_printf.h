/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:26:07 by hrother           #+#    #+#             */
/*   Updated: 2023/10/07 13:39:39 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define UPCASE_HEX "0123456789ABCDEF"
# define LOWCASE_HEX "0123456789abcdef"

int		ft_printf(const char *str, ...);

int		ft_print_c(char c);
int		ft_print_s(char *s);
int		ft_print_i(int n);
int		ft_print_x(unsigned int n, char *base);
int		ft_print_u(unsigned int n);
int		ft_print_p(void *ptr);
size_t	ft_strlen(const char *str);

#endif
