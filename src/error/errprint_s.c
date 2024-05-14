/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errprint_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:02:36 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 13:49:54 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/errprintf.h"

int	errprint_s(char *s)
{
	if (s)
		return (write(STDERR_FILENO, s, ft_strlen(s)));
	else
		return (write(STDERR_FILENO, "(null)", 6));
}
