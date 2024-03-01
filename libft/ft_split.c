/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:37:45 by hrother           #+#    #+#             */
/*   Updated: 2023/09/11 18:14:55 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_w(char const *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			wcount++;
		while (s[i] != c && s[i])
			i++;
	}
	return (wcount);
}

static void	ft_free(char **s, int i)
{
	while (i >= 0)
		free(s[i--]);
	free(s);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	int		wcount;
	char	**res;

	wcount = count_w(s, c);
	res = (char **)malloc((wcount + 1) * sizeof(char *));
	if (!res)
		return (res);
	i = 0;
	while (i < wcount)
	{
		len = 0;
		while (*s == c)
			s++;
		while (s[len] != c && s[len])
			len++;
		res[i] = ft_substr(s, 0, len);
		if (!res[i])
			return (ft_free(res, i), NULL);
		s += len;
		i++;
	}
	res[wcount] = NULL;
	return (res);
}
