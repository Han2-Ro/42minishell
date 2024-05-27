/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errprint_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:05:17 by hrother           #+#    #+#             */
/*   Updated: 2024/05/27 17:04:09 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errprintf.h"

int	errprint_i(int n)
{
	unsigned int	nbr;
	int				c_count;
	char			c;

	c_count = 0;
	if (n < 0)
	{
		c_count += write(STDERR_FILENO, "-", 1);
		nbr = -n;
	}
	else
		nbr = n;
	if (nbr >= 10)
		c_count += errprint_i(nbr / 10);
	c = nbr % 10 + '0';
	c_count += write(1, &c, 1);
	return (c_count);
}
