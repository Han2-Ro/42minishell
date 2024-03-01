/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:05:17 by hrother           #+#    #+#             */
/*   Updated: 2023/09/16 19:08:40 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_i(int n)
{
	unsigned int	nbr;
	int				c_count;
	char			c;

	c_count = 0;
	if (n < 0)
	{
		c_count += write(1, "-", 1);
		nbr = -n;
	}
	else
		nbr = n;
	if (nbr >= 10)
		c_count += ft_print_i(nbr / 10);
	c = nbr % 10 + '0';
	c_count += write(1, &c, 1);
	return (c_count);
}
