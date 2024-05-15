/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:42:00 by hrother           #+#    #+#             */
/*   Updated: 2024/05/15 20:29:16 by aprevrha         ###   ########.fr       */
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
