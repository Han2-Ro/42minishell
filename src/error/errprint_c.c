/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errprint_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:01:18 by hrother           #+#    #+#             */
/*   Updated: 2024/05/14 14:04:21 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/errprintf.h"

int	errprint_c(char c)
{
	return (write(STDERR_FILENO, &c, 1));
}
