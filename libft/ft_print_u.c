/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:05:17 by hrother           #+#    #+#             */
/*   Updated: 2023/09/16 19:08:25 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_u(unsigned int n)
{
	int				c_count;
	char			c;

	c_count = 0;
	if (n >= 10)
		c_count += ft_print_i(n / 10);
	c = n % 10 + '0';
	c_count += write(1, &c, 1);
	return (c_count);
}
