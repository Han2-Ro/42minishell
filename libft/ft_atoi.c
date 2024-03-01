/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:47:16 by hrother           #+#    #+#             */
/*   Updated: 2023/09/13 14:57:00 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_atoi(char *str)
{
	int	result;
	int	sign;
	int	digit;

	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	sign = -1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	result = 0;
	while (*str)
	{
		if (*str < '0' || '9' < *str)
		{
			break ;
		}
		digit = *str - '0';
		result = result * 10 - digit;
		str++;
	}
	return (result * sign);
}
