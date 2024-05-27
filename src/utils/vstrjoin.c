/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vstrjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:41:35 by hrother           #+#    #+#             */
/*   Updated: 2024/05/27 17:05:33 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	vstrjoin_2(int nbr_of_strs, int size, char *result, va_list args)
{
	const char	*arg;
	int			arg_count;

	result[0] = '\0';
	arg_count = 0;
	while (arg_count < nbr_of_strs)
	{
		arg = va_arg(args, const char *);
		arg_count++;
		ft_strlcat(result, arg, size + 1);
	}
}

char	*vstrjoin(int nbr_of_strs, ...)
{
	va_list		args;
	const char	*arg;
	size_t		size;
	char		*result;
	int			arg_count;

	size = 0;
	va_start(args, nbr_of_strs);
	arg_count = 0;
	while (arg_count < nbr_of_strs)
	{
		arg = va_arg(args, const char *);
		size += ft_strlen(arg);
		arg_count++;
	}
	va_end(args);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	va_start(args, nbr_of_strs);
	vstrjoin_2(nbr_of_strs, size, result, args);
	va_end(args);
	return (result);
}
