/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:20:19 by dernst            #+#    #+#             */
/*   Updated: 2025/06/17 10:26:36 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

size_t	inside_quote(char c, char *quote)
{
	if (*quote == 0)
	{
		if (c == '\"' || c == '\'')
		{
			*quote = c;
			return (2);
		}
		return (0);
	}
	else
	{
		if (c == *quote)
		{
			*quote = 0;
			return (3);
		}
		return (1);
	}
}

void	rm_inside_quote(char *args, size_t *j, char *quote)
{
	*j += 1;
	if (args[*j] && args[*j] == *quote)
	{
		*quote = 0;
		*j += 1;
	}
}

void	rm_inside_expand(char **temp, char *args, size_t *j, size_t *k, size_t *expand)
{
	*expand = 1;
	(*temp)[*k] = args[*j];
	*j += 1;
	*k += 1;
	while (args[*j] && args[*j] != EXPAND)
	{
		(*temp)[*k] = args[*j];
		*j += 1;
		*k += 1;
	}
	if (args[*j] == EXPAND)
	{
		*expand = 0;
	}
}

char	**remove_quotes(char **args)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	expand;
	char	*temp;
	char	quote;

	i = 0;
	j = 0;
	k = 0;
	quote = 0;
	expand = 0;
	if (!args)
		return (NULL);
	while (args[i])
	{
		temp = ft_calloc((ft_strlen(args[i]) + 1), sizeof(char));
		if (!temp)
			return (NULL);
		while (args[i][j])
		{
			if (args[i][j] == EXPAND || expand)
				rm_inside_expand(&temp, args[i], &j, &k, &expand);
			if (!expand && inside_quote(args[i][j], &quote) > 1)
				rm_inside_quote(args[i], &j, &quote);
			else if (!expand)
				temp[k++] = args[i][j++];
		}
		temp[k] = '\0';
		k = 0;
		j = 0;
		free(args[i]);
		args[i++] = temp;
	}
	return (args);
}
