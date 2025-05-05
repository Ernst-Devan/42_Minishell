/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:20:19 by dernst            #+#    #+#             */
/*   Updated: 2025/04/28 17:16:04 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

size_t	inside_quote(char c, char *quote)
{
	if (*quote == 0)
	{
		if (c == '\"' || c == '\'')
		{
			*quote = c;
			return(1);
		}
		return (0);
	}
	else 
	{
		if (c == *quote)
		{
			*quote = 0;
			return(1);
		}
		return (1);
	}	
}

char *skip_space(char *input)
{
	char	*buffer;
	char	quote;
	size_t	i;
	size_t	j;
	size_t	inside;

	inside = 0;
	i = 0;
	j = 0;
	quote = 0;
	buffer = malloc((ft_strlen(input) + 1) * sizeof(char));
	while(input[j])
	{
		if (inside == 0)
		{
			if (input[j] == ' ')
			{
				buffer[i++] = input[j];
				while(input[j] && input[j] == ' ')
					j++;
				if (!input[j])
					break;
			}
		}
		inside = inside_quote(input[j], &quote);
		buffer[i++] = input[j];
		j++;
	}
	if (quote != 0)
	{
		ft_printf("Unclosed quotes\n");
		
	}
	buffer[i] = '\0';
	free(input);
	return (buffer);
}
