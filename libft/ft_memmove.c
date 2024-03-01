/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:42:03 by hrother           #+#    #+#             */
/*   Updated: 2023/09/12 16:01:29 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				direction;
	unsigned char		*p_dest;
	const unsigned char	*p_src;

	if (!dest && !src)
		return (NULL);
	p_dest = dest;
	p_src = src;
	if (dest < src)
		direction = 1;
	else
	{
		direction = -1;
		p_dest += n - 1;
		p_src += n - 1;
	}
	while (n)
	{
		*p_dest = *p_src;
		p_dest += direction;
		p_src += direction;
		n--;
	}
	return (dest);
}
