/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:20:19 by dernst            #+#    #+#             */
/*   Updated: 2025/06/25 15:48:51 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stddef.h>

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

void	rm_quotes(char *arg, size_t *expand, char *quote)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (arg[j])
	{
		if (arg[j] == EXPAND)
			*expand ^= 1;
		if ((!*expand && inside_quote(arg[j], quote) > 1))
		{
			j++;
			continue ;
		}
		if (!arg[i] || !arg[j])
			break ;
		arg[i++] = arg[j++];
	}
	arg[i] = '\0';
}

size_t	manage_quotes(char **args)
{
	size_t	i;
	size_t	expand;
	char	quote;

	i = 0;
	expand = 0;
	quote = 0;
	if (!args)
		return (1);
	while (args[i])
	{
		rm_quotes(args[i], &expand, &quote);
		i++;
	}
	return (0);
}
