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
			return(2);
		}
		return (0);
	}
	else 
	{
		if (c == *quote)
		{
			*quote = 0;
			return(3);
		}
		return (1);
	}	
}

char	**remove_quotes(char **splited_cmds)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*temp;
	char	quote;

	i = 0;
	j = 0;
	k = 0;
	quote = 0;
	if (!splited_cmds)
		return(NULL);
	while(splited_cmds[i])
	{
		temp = malloc(ft_strlen(splited_cmds[i]) + 1);
		while (splited_cmds[i][j])
		{
			if (inside_quote(splited_cmds[i][j], &quote) > 1)
			{
				j++;
				if (splited_cmds[i][j] && splited_cmds[i][j] == quote)
				{
					quote = 0;
					j++;
				}
			}
			else
				temp[k++] = splited_cmds[i][j++];
		}
		temp[k] = '\0';
		k = 0;
		j = 0;
		free(splited_cmds[i]);
		splited_cmds[i++] = temp;
	}
	return (splited_cmds);
}

char *skip_space(char *input, int *error_code)
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
	buffer = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	while(input[j])
	{
		if (j == 0)
		{
			while(ft_isspace(input[j]))
				j++;
		}
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
	buffer[i] = '\0';
	if (quote != 0)
	{
		printf("Unclosed quotes : %s\n", buffer);
		*error_code = 2;	
	}
	free(input);
	return (buffer);
}
