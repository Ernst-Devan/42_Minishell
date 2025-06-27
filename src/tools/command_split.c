/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:54:27 by dernst            #+#    #+#             */
/*   Updated: 2025/06/24 18:14:46 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "parsing.h"

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
					splited[i++] = input[j++];
				splited[i++] = input[j++];
			}
			if (!input[j] || input[j] == c)
				break ;
		}
		splited[i++] = input[j++];
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
	while (input[count])
	{
		if (!inside_quote(input[count], &quotes))
		{
			if (input[count] == EXPAND)
			{
				count++;
				while (input[count] != EXPAND)
					count++;
			}
			if (input[count] == c)
				break ;
		}
		count++;
	}
	return (count);
}

char	**split_cmd(char *input, char c)
{
	char	**split;
	char	*cpy;
	size_t	count_w;
	size_t	count_l;
	size_t	i;

	count_w = count_split(input, c) + 1;
	split = ft_calloc((count_w + 1), sizeof(char *));
	cpy = input;
	i = 0;
	while (split && i < count_w)
	{
		count_l = nb_letter(cpy, c);
		split[i] = ft_calloc((count_l * 2 + ft_strlen(cpy) + 1), sizeof(char));
		if (!split[i])
		{
			free_lstr(split);
			return (NULL);
		}
		split[i] = split_insert(split[i], cpy, c);
		cpy += count_l + 1;
		i++;
	}
	return (split);
}
