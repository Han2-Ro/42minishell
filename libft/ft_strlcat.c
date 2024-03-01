/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:42:00 by hrother           #+#    #+#             */
/*   Updated: 2023/09/13 14:59:03 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			dest_len;

	if (!dst && !dst && size == 0)
		return (0);
	dest_len = ft_strlen(dst);
	if (dest_len >= size)
		return (ft_strlen(src) + size);
	i = 0;
	while (src[i] != '\0' && dest_len + i + 1 < size)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	while (src[i] != '\0')
		i++;
	return (dest_len + i);
}
