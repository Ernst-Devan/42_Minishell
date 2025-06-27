/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:13:07 by dernst            #+#    #+#             */
/*   Updated: 2025/06/13 08:53:22 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

size_t	detect_lim(char *input, char **buffer, size_t *i, size_t *j)
{
	if (ft_isspace(input[*i]))
		*i += 1;
	while (check_delimiter(input[*i], LIM))
	{
		(*buffer)[*j] = input[*i];
		*j += 1;
		*i += 1;
	}
	if ((*buffer)[*j - 1] != SEP)
	{
		(*buffer)[*j] = SEP;
		*j += 1;
	}
	return (0);
}

size_t	lexer(char **input)
{
	char	*buffer;
	char	quote;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	quote = 0;
	buffer = ft_calloc(ft_strlen(*input) + count_chars(*input, LIM) + 1, 1);
	if (!buffer)
		return (EXPAND);
	while ((*input)[i])
	{
		if ((*input)[i] && !inside_quote((*input)[i], &quote)
				&& check_delimiter((*input)[i], LIM))
			detect_lim(*input, &buffer, &i, &j);
		else if (j >= 1 && buffer[j - 1] == SEP && (*input)[i] == SEP)
			i++;
		else if ((*input)[i])
			buffer[j++] = (*input)[i++];
	}
	buffer[j] = '\0';
	free(*input);
	*input = buffer;
	return (0);
}
