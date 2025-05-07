/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:54:27 by dernst            #+#    #+#             */
/*   Updated: 2025/05/06 12:21:07 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parsing.h>
#include <stddef.h>

// Check | not inside quotes

size_t	count_split(char *input, char c)
{
	char	quotes;
	size_t	count;

	count = 0;
	quotes = 0;
	while (*input)
	{
		if (!inside_quote(*input, &quotes))
		{
			if (*input == c)
				count++;
		}
		input++;
	}
	return (count);
}

size_t	nb_letter(char *input, char c)
{
	char	quotes;
	size_t	count;
	
	count = 0;
	quotes = 0;
	while(*input)
	{
		if (!inside_quote(*input, &quotes))
		{
			if (*input == c)
				break;
		} 
		count++; 
		input++;
	}
	return (count);
}

//! free correctly the splited malloc

char	*split_insert(char *splited, char *input, char c)
{
	size_t	i;
	char	quotes;

	i = 0;
	quotes = 0;
	while (*input)
	{
		if (!inside_quote(*input, &quotes))
		{
			if (*input == c)
				break;
		}
		splited[i] = *input;
		i++;
		input++;
	}
	splited[i] = '\0';
	return (splited);
}


// FREE THE FUNCTION IF MALLOC FAILED
char	**split_cmd(char *input, char c)
{
	char	**split;
	char	*cpy_input;
	size_t	count_w;
	size_t	count_l;
	size_t	i;

	count_w = count_split(input, c) + 1;
	split = malloc((count_w + 1) * sizeof(char *));
	if (!split)
		free(split);
	cpy_input = input;
	i = 0;
	while (i < count_w)
	{
		count_l = nb_letter(cpy_input, c);
		split[i] = malloc((count_l + 1) * sizeof(char));
		split[i] = split_insert(split[i], cpy_input, c);
		cpy_input += count_l + 1;
		i++;
	}
	split[i] = NULL;
	return (split);
}
