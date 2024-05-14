/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errprintf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:38:56 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 15:05:29 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/errprintf.h"

int	ft_convert(const char *str, va_list args)
{
	if (*str == 'c')
		return (errprint_c(va_arg(args, int)));
	else if (*str == 's')
		return (errprint_s(va_arg(args, char *)));
	else if (*str == 'i' || *str == 'd')
		return (errprint_i(va_arg(args, int)));
	else if (*str == '%')
		return (errprint_c(*str));
	errprint_c('%');
	errprint_c(*str);
	return (2);
}

int	errprintf(const char *str, ...)
{
	va_list	args;
	int		c_count;

	c_count = -1;
	va_start(args, str);
	c_count = verrprintf(str, args);
	va_end(args);
	return (c_count);
}


int	verrprintf(const char *str, va_list args)
{
	int		c_count;

	if (!str)
		return (-1);
	c_count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			c_count += ft_convert(str, args);
		}
		else
			c_count += errprint_c(*str);
		str++;
	}
	return (c_count);
}