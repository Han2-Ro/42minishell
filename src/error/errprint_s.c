/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errprint_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:02:36 by hrother           #+#    #+#             */
/*   Updated: 2024/05/27 17:05:08 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errprintf.h"

int	errprint_s(char *s)
{
	if (s)
		return (write(STDERR_FILENO, s, ft_strlen(s)));
	else
		return (write(STDERR_FILENO, "(null)", 6));
}
