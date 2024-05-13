/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:21:19 by hrother           #+#    #+#             */
/*   Updated: 2024/05/13 18:37:06 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/get_next_line.h"

int	ft_add_next_buffer(int fd, char **str)
{
	char	*buffer;
	int		bytes_read;
	char	*result;

	buffer = malloc(1 * sizeof(char));
	if (!buffer)
		return (-1);
	gnl_bzero(buffer, 1);
	bytes_read = read(fd, buffer, 1);
	if (bytes_read == 0)
		return (free(buffer), bytes_read);
	else if (bytes_read < 0)
	{
		free(*str);
		*str = NULL;
		return (free(buffer), bytes_read);
	}
	result = gnl_strjoin(*str, buffer);
	free(*str);
	*str = result;
	return (free(buffer), bytes_read);
}

char	*ft_get_next_line(int fd)
{
	char	*str;
	int		i;

	if (fd < 0 || fd >= 1024)
		return (NULL);
	str = malloc(sizeof(char));
	str[0] = '\0';
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n')
	{
		if (ft_add_next_buffer(fd, &str) <= 0)
			break ;
		if (!str)
			return (NULL);
	}
	if (str && *str)
		return (str);
	else
		return (free(str), NULL);
}
