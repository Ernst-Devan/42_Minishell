/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:06:59 by dernst            #+#    #+#             */
/*   Updated: 2025/01/28 17:43:02 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_null_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

int	read_file(char (*buffer)[BUFFER_SIZE], int fd, char **result)
{
	int	bytes_read;

	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read > 0)
		(*buffer)[bytes_read] = '\0';
	if (bytes_read <= 0)
	{
		(*buffer)[0] = '\0';
		buffer = NULL;
	}
	(void)*result;
	return (bytes_read);
}

size_t	get_buffer(char *buffer, char **line, int bytes_read, size_t *is_end)
{
	char	*temp_result;
	size_t	buffer_start;

	buffer_start = 0;
	temp_result = gnl_ft_substr(buffer, bytes_read, is_end, &buffer_start);
	*line = gnl_ft_strjoin(*line, temp_result);
	free(temp_result);
	temp_result = NULL;
	return (buffer_start);
}

char	*update_result(char (*buffer)[BUFFER_SIZE], char **result, int fd)
{
	int		bytes_read;
	size_t	is_end;
	size_t	start;

	is_end = 0;
	start = 0;
	bytes_read = gnl_ft_strlen(*buffer, 0);
	if (bytes_read == 0)
	{
		bytes_read = read_file(buffer, fd, result);
		if (bytes_read <= 0)
			return (gnl_null_free(result));
	}
	while (is_end == 0)
	{
		start = get_buffer(*buffer, result, bytes_read, &is_end);
		if (is_end == 0)
			bytes_read = read_file(buffer, fd, result);
		if (bytes_read == 0)
			return (*result);
		if (bytes_read == -1)
			return (gnl_null_free(result));
	}
	gnl_ft_memmove(*buffer, *buffer + start, bytes_read - start);
	return (*result);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*result;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	if (fd < 0)
		return (NULL);
	result = gnl_ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	result[0] = '\0';
	result = update_result(&buffer, &result, fd);
	return (result);
}
