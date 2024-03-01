/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:38:56 by hrother           #+#    #+#             */
/*   Updated: 2023/10/02 16:46:58 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert(const char *str, va_list args)
{
	if (*str == 'c')
		return (ft_print_c(va_arg(args, int)));
	else if (*str == 's')
		return (ft_print_s(va_arg(args, char *)));
	else if (*str == 'i' || *str == 'd')
		return (ft_print_i(va_arg(args, int)));
	else if (*str == 'x')
		return (ft_print_x(va_arg(args, unsigned int), LOWCASE_HEX));
	else if (*str == 'X')
		return (ft_print_x(va_arg(args, unsigned int), UPCASE_HEX));
	else if (*str == 'u')
		return (ft_print_u(va_arg(args, unsigned int)));
	else if (*str == 'p')
		return (ft_print_p(va_arg(args, void *)));
	else if (*str == '%')
		return (ft_print_c(*str));
	ft_print_c('%');
	ft_print_c(*str);
	return (2);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		c_count;

	if (!str)
		return (-1);
	va_start(args, str);
	c_count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			c_count += ft_convert(str, args);
		}
		else
			c_count += ft_print_c(*str);
		str++;
	}
	va_end(args);
	return (c_count);
}
