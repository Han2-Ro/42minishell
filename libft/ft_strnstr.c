/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:15:39 by hrother           #+#    #+#             */
/*   Updated: 2023/09/13 14:59:50 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < len && big[j] != '\0')
	{
		i = 0;
		while ((big[j + i] == little[i] || little[i] == '\0') && j + i <= len)
		{
			if (little[i] == '\0')
			{
				return ((char *)big + j);
			}
			i++;
		}
		j++;
	}
	if (*little == '\0')
		return ((char *)big + j);
	return (NULL);
}
