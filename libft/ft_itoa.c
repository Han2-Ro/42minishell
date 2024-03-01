/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:00:30 by hrother           #+#    #+#             */
/*   Updated: 2023/09/11 18:47:49 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_numb_len(int nbr)
{
	int	len;

	len = 1;
	if (nbr < 0)
		len ++;
	while (nbr > 9 || nbr < -9)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				len;
	unsigned int	nbr;

	len = get_numb_len(n);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (res);
	res[len--] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		nbr = -n;
	}
	else
		nbr = n;
	res[len--] = nbr % 10 + '0';
	while (nbr > 9)
	{
		nbr /= 10;
		res[len--] = nbr % 10 + '0';
	}
	return (res);
}
