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
#include "parsing.h"
#include <stddef.h>

// Check | not inside quotes

size_t	count_split(char *input, char c)
{
	char	quotes;
	size_t	count;
	size_t	i;

	count = 0;
	quotes = 0;
	i = 0;
	while (input[i])
	{
		if (!inside_quote(input[i], &quotes))
		{
			if (input[i] == EXPAND)
			{
				i++;
				while (input[i] != EXPAND)
					i++;
			}
			if (input[i] == c)
				count++;
		}
		i++;
	}
	return (count);
}

char	*split_insert(char *splited, char *input, char c)
{
	size_t	i;
	size_t	j;
	char	quotes;

	i = 0;
	j = 0;
	quotes = 0;
	while (input[j])
	{
		if ((!inside_quote(input[j], &quotes)))
		{
			if (input[j] == EXPAND)
			{
				splited[i++] = input[j++];
				while (input[j] && input[j] != EXPAND)
				{
					splited[i] = input[j];
					i++;
					j++;
				}
				splited[i++] = input[j++];
			} 
			if (!input[j] || input[j] == c)
				break;
		}
		if (!input[j])
			break;
		splited[i] = input[j];
		i++;
		j++;
	}
	splited[i] = '\0';
	return (splited);
}

size_t	count_char(char *input, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == c)
			count++;
		i++;
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
			if (*input == EXPAND)
			{
				input++;
				count++;
				while (*input != EXPAND)
				{
					input++;
					count++;
				}
			}
			if (*input == c)
				break;
		} 
		count++; 
		input++;
	}
	return (count);
}

char	**split_cmd(char *input, char c)
{
	char	**split;
	char	*cpy_input;
	size_t	count_w;
	size_t	count_l;
	size_t	i;

	count_w = count_split(input, c) + 1;
	split = ft_calloc((count_w + 1), sizeof(char *));
	if (!split)
	{
		free(split);
		return (NULL);
	}
	cpy_input = input;
	i = 0;
	while (i < count_w)
	{
		count_l = nb_letter(cpy_input, c);
		split[i] = ft_calloc((count_l * 2 + ft_strlen(cpy_input) + 1),sizeof(char));
		if (!split[i])
		{
			free_lstr(split);
			return (NULL);
		}
		split[i] = split_insert(split[i], cpy_input, c);
		cpy_input += count_l + 1;
		i++;
	}
	split[i] = NULL;
	display_lstr(split);
	return (split);
}
