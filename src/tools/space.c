/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:28:47 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 11:28:48 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stddef.h>

char	*skip_first_space(char *variable)
{
	char	*buffer;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	buffer = ft_calloc(ft_strlen(variable) + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (variable[i] == EXPAND)
		buffer[j++] = variable[i++];
	while (variable[i] && ft_isspace(variable[i]))
	{
		i++;
	}
	while (variable[i])
	{
		buffer[j++] = variable[i++];
	}
	buffer[j] = '\0';
	free(variable);
	return (buffer);
}

size_t	count_first_space(char *input)
{
	size_t	count;

	count = 0;
	while (*input && ft_isspace(*input))
	{
		count++;
		input++;
	}
	return (count);
}

size_t	skip_space(char **buffer, char *input, size_t *i, size_t *j)
{
	if (ft_isspace(input[*i]))
	{
		(*buffer)[*j] = SEP;
		*j += 1;
		while (input[*i] && ft_isspace(input[*i]))
			*i += 1;
	}
	if (!(input[*i]))
		return (1);
	return (0);
}

size_t	manage_space(char **input)
{
	char	*buffer;
	char	quote;
	size_t	i;
	size_t	j;

	buffer = ft_calloc(ft_strlen(*input) + 1, sizeof(char));
	if (!buffer)
	{
		free(*input);
		return (E_MALLOC);
	}
	quote = 0;
	i = count_first_space(*input);
	j = 0;
	while ((*input)[i])
	{
		if (quote == 0 && skip_space(&buffer, *input, &i, &j))
			break ;
		inside_quote((*input)[i], &quote);
		buffer[j++] = (*input)[i++];
	}
	buffer[j] = '\0';
	free(*input);
	*input = buffer;
	return (0);
}
