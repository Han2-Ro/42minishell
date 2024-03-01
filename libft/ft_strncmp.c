/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:14:25 by hrother           #+#    #+#             */
/*   Updated: 2023/09/12 12:57:02 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	uc1;
	unsigned char	uc2;

	if (n == 0)
		return (0);
	i = 0;
	while (i + 1 < n)
	{
		uc1 = (unsigned char)s1[i];
		uc2 = (unsigned char)s2[i];
		if (uc1 != uc2 || uc1 == '\0')
			break ;
		i++;
	}
	uc1 = (unsigned char)s1[i];
	uc2 = (unsigned char)s2[i];
	return (uc1 - uc2);
}
