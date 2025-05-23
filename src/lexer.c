/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:13:07 by dernst            #+#    #+#             */
/*   Updated: 2025/04/22 11:13:55 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <readline/readline.h>
#include <stddef.h>

char *lexer(char *input) 
{
	char	*buffer;
	char	*input_adress;
	size_t	i;
	size_t	buffer_size;
	char	quote;

	quote = 0;
	// Find a better allocation size
	buffer_size = ft_strlen(input) + count_characters(input, DELIMITER) * 10 + 1;
	i = 0;
	buffer = ft_calloc(buffer_size, sizeof(char));
	if (!buffer)
		return (NULL);
	input_adress = input;
	while (*input)
	{
		if (inside_quote(*input, &quote))
			buffer[i++] = *input++;
		else
		{
			if (check_delimiter(*input, "<>| ") == 1)
			{
				if (*input == ' ')
					input++;
				buffer[i++] = SEPARATOR;
				while(check_delimiter(*input, "<>|") == 1)
					buffer[i++] = *input++;
				if (buffer[i - 1] != SEPARATOR)
					buffer[i++] = SEPARATOR;
				if (*input == ' ')
					input++;
			}
			else if (*input && *input != '\'' && *input != '\"')
				buffer[i++] = *input++;
		}
	}
	buffer[i] = '\0';
	free(input_adress);
	return (buffer);
}
