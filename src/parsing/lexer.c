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
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>

size_t	lexer(char **input)
{
	char	*buffer;
	char	quote;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	quote = 0;
	buffer = ft_calloc(ft_strlen(*input) + count_characters(*input, DELIMITER) + 1, 1);
	if (!buffer)
	{
		free(*input);
		return (1);
	}
	while ((*input)[i])
	{
		if ((*input)[i] && !inside_quote((*input)[i], &quote) && check_delimiter((*input)[i], "<>|\xE1"))
		{
			if (ft_isspace((*input)[i]))
				i++;
			while (check_delimiter((*input[i]), "<>|"))
				buffer[j++] = (*input)[i++];
			if (buffer[j - 1] != SEPARATOR)
				buffer[j++] = SEPARATOR;
		}
		else if (j >= 1 && buffer[j - 1] == SEPARATOR && (*input)[i] == SEPARATOR)
			i++;
		else if ((*input)[i])
			buffer[j++] = (*input)[i++];
	}
	buffer[j] = '\0';
	free(*input);
	*input = buffer;
	return (0);
}
