/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:21:19 by hrother           #+#    #+#             */
/*   Updated: 2023/11/06 18:49:06 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_after(char **str, int len)
{
	char	*res;
	char	*remainder;

	if (len <= 0)
		len = gnl_strlen(*str);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (free(*str), *str = NULL, NULL);
	gnl_strlcpy(res, *str, len + 1);
	remainder = malloc((gnl_strlen(*str) - len + 1) * sizeof(char));
	if (!remainder)
		return (free(res), free(*str), *str = NULL, NULL);
	gnl_strlcpy(remainder, *str + len, gnl_strlen(*str) - len + 1);
	free(*str);
	*str = remainder;
	return (res);
}

char	*init_str(char *str)
{
	if (!str)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	return (str);
}

int	add_next_buffer(int fd, char **str)
{
	char	*buffer;
	int		bytes_read;
	char	*result;

	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return (-1);
	gnl_bzero(buffer, BUFFER_SIZE);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
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

char	*get_next_line(int fd)
{
	static char	*str[1024];
	int			nl_i;

	if (fd < 0 || fd >= 1024)
		return (NULL);
	str[fd] = init_str(str[fd]);
	if (!str[fd])
		return (NULL);
	nl_i = get_i_of_newline(str[fd]);
	while (nl_i < 0)
	{
		if (add_next_buffer(fd, &str[fd]) <= 0)
			break ;
		if (!str[fd])
			return (NULL);
		nl_i = get_i_of_newline(str[fd]);
	}
	if (str[fd] && *str[fd])
		return (trim_after(&str[fd], nl_i + 1));
	else
		return (free(str[fd]), str[fd] = NULL, NULL);
}
